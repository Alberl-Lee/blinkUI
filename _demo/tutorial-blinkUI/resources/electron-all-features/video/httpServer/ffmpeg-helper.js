"use strict";
const ffmpegPath = require("@ffmpeg-installer/ffmpeg").path;
const process = require("child_process");

function findVideoInfo(reg, text) {
  let matchArr = reg.exec(text);
  let infoFound;
  if (matchArr && matchArr.length > 1) {
    infoFound = matchArr[1].trim();
  }
  return infoFound;
}

function transformDuration(duration) {
  if (!duration) {
    return 0;
  }
  let arr = duration.split(":");
  if (arr.length == 3) {
    return parseInt(arr[0]) * 3600 + parseInt(arr[1]) * 60 + parseInt(arr[2]);
  }
  return 0;
}

var videoSupport = function (videoPath) {
  let p = new Promise(function (resolve, reject) {
    let command = `${ffmpegPath} -i ${videoPath}`;
    process.exec(command, { encoding: "utf-8" }, function (error, stdout, stderr) {
      if (error) {
        let str = error.stack;
        let videoReg = /Video:((\w|\s)+)/gi;
        let videoCodec = findVideoInfo(videoReg, str);
        let audioReg = /Audio:((\w|\s)+)/gi;
        let audioCodec = findVideoInfo(audioReg, str);
        let durationReg = /Duration:((\w|:|\s)+)/gi;
        let duration = findVideoInfo(durationReg, str);
        let durationSeconds = transformDuration(duration);
        console.log("videoCodec:" + videoCodec + ",audioCodec:" + audioCodec + ",duration:" + durationSeconds);
        if (!videoPath || !audioCodec || !durationSeconds) {
          reject("err video file");
          return;
        }
        var checkResult = {
          videoCodecSupport: false,
          audioCodecSupport: false,
          duration: durationSeconds,
        };
        // H5自带支持的格式：mp4, webm, ogg  其实可以不用检查，全部使用ffmpeg
        if (videoCodec == "h264" || videoCodec == "vp8" || videoCodec == "theora") {
          checkResult.videoCodecSupport = true;
        }
        // aac, vorbis
        if (audioCodec == "aac" || audioCodec == "vorbis") {
          checkResult.audioCodecSupport = true;
        }
        resolve(checkResult);
        return;
      }
      reject("no video info:" + videoPath);
    });
  });
  return p;
};
export { videoSupport };
