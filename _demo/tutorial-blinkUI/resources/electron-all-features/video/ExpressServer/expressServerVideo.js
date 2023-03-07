(function () {
  "use strict";
  const express = require("express");
  const fs = require("fs");
  const ffmpegPath = require("@ffmpeg-installer/ffmpeg").path;
  const ffmpeg = require("fluent-ffmpeg");
  ffmpeg.setFfmpegPath(ffmpegPath);

  let ffmpegCommand = null;
  const app = express();
  app.get("/video", function (req, res) {
    let pathSrc = req.query.video;
    let stat = fs.statSync(pathSrc);
    let fileSize = stat.size;

    if (ffmpegCommand !== null) {
      ffmpegCommand.kill();
      ffmpegCommand = null;
    }
    ffmpegCommand = ffmpeg(pathSrc)
      .input(pathSrc)
      .nativeFramerate()
      .videoCodec("libx264")
      .audioCodec("aac")
      .format("mp4")
      .seekInput(0)
      .outputOptions(
        "-movflags",
        "frag_keyframe+empty_moov+faststart",
        "-preset",
        "veryfast", //以损失画质换取流畅度
        "-g",
        "18"
      )
      .on("progress", function (progress) {
        console.log("time: " + progress.timemark);
      })
      .on("error", function (err) {
        console.log("An error occurred: " + err.message);
      })
      .on("end", function () {
        console.log("Processing finished !");
      });
    let videoStream = ffmpegCommand.pipe();
    videoStream.pipe(res);
  });

  app.listen(6789, () => {
    console.log("localhost:6789");
  });
})();
