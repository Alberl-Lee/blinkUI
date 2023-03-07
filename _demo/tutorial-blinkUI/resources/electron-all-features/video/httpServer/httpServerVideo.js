"use strict";
const ffmpegPath = require("@ffmpeg-installer/ffmpeg").path;
const ffmpeg = require("fluent-ffmpeg");
ffmpeg.setFfmpegPath(ffmpegPath);
const http = require("http");

function getParam(url, key) {
  var param = new Object();
  var item = new Array();
  var urlList = url.split("?");
  var req;
  if (urlList.length == 1) {
    req = urlList[0];
  } else {
    req = urlList[1];
  }
  var list = req.split("&");
  for (var i = 0; i < list.length; i++) {
    item = list[i].split("=");
    param[item[0]] = item[1];
  }
  return param[key] ? param[key] : null;
}

export default class httpServerVideo {
  constructor(props) {
    this._videoServer;
    this._videoSourceInfo;
    this._ffmpegCommand;
    this._request;
  }

  set videoSourceInfo(info) {
    this._videoSourceInfo = info;
  }

  get videoSourceInfo() {
    return this._videoSourceInfo;
  }

  killFfmpegCommand() {
    if (this._ffmpegCommand) {
      this._ffmpegCommand.kill();
      this._ffmpegCommand = null;
    }
  }

  createServer() {
    if (!this.videoSourceInfo) return;

    if (!this._videoServer) {
      (this._videoServer = http
        .createServer((request, response) => {
          this._request = request;
          console.log("on request", request.url);
          var startTime = parseInt(getParam(request.url, "startTime"));

          let videoSourcePath = getParam(request.url, "video");
          this.videoSourceInfo = { videoSourcePath: videoSourcePath, checkResult: false };

          this.play(startTime, response);
        })
        .listen(8888)),
        () => {
          console.log("服务器启动成功：http://localhost:8888");
        };
    } else {
      // this._videoServer.listen(3000, () => {
      // this._videoServer.emit("get");
      // this._videoServer.get(this._request.url);
      // 手动触发请求
      // http.get("http://127.0.0.1:8888" + this._request.url);
      // 手动触发请求
      // 在浏览器里输入http://127.0.0.1:8888?startTime=0，也会触发这个请求，并且自动下载了视频
      // http
      //   .get("http://127.0.0.1:8888?startTime=0", (response) => {
      //     // 前面createServer已经有响应了，这里就不用处理了
      //   })
      //   .on("error", (err) => {
      //     console.log("Error: ", err.message);
      //   });
    }
  }

  play(startTime, response) {
    let videoCodec = this.videoSourceInfo.checkResult.videoCodecSupport ? "copy" : "libx264";
    let audioCodec = this.videoSourceInfo.checkResult.audioCodecSupport ? "copy" : "aac";
    this.killFfmpegCommand();
    this._ffmpegCommand = ffmpeg(this.videoSourceInfo.videoSourcePath)
      // this._ffmpegCommand = ffmpeg() // 这个不行，会晚2秒才开始显示出视频
      .input(this.videoSourceInfo.videoSourcePath)
      .nativeFramerate()
      .videoCodec(videoCodec)
      .audioCodec(audioCodec)
      .format("mp4")
      .seekInput(startTime)
      .outputOptions(
        "-movflags",
        "frag_keyframe+empty_moov+faststart",
        "-preset",
        "veryfast", //以损失画质换取流畅度，不然会比express那个晚0.5秒显示
        "-g",
        "18"
      )
      .on("progress", function (progress) {
        console.log("time: " + progress.timemark);
        // 这里就可以获得时间，不需要再额外用videoSupport、StreamPlayTech类去获取了
      })
      .on("error", function (err) {
        console.log("An error occurred: " + err.message);
      })
      .on("end", function () {
        console.log("Processing finished !");
      });
    let videoStream = this._ffmpegCommand.pipe();
    videoStream.pipe(response); // 把视频流反馈给客户端
  }

}
export { httpServerVideo };

let httpServer;
if (!httpServer) httpServer = new httpServerVideo();
httpServer.videoSourceInfo = { videoSourcePath: "", checkResult: false };
httpServer.createServer();
console.log("createVideoServer success");
