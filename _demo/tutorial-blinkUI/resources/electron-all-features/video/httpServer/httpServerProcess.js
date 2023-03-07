(function () {
  "use strict";

  const path = require("path");
  const cp = require("child_process");
  const pathFile = path.join(__dirname, "video/httpServer/httpServerVideo.js");
  cp.fork(pathFile);
})();
