// 模态框
let g_idDialogNow;
$(".modal-close, .modal-background, .delete").click(function () {
  $(this).parent(".modal").removeClass("is-active");
  $(g_idDialogNow).trigger("dialog-close", "OK");
});

function setDialogText(text, selectorDlg = "#modalDialog") {
  $(selectorDlg).find(".modal-value").text(text);
}

function showModalDialog(text, selectorDlg = "#modalDialog") {
  $(selectorDlg).addClass("is-active");
  setDialogText(text, selectorDlg);
  g_idDialogNow = selectorDlg;
}

$("#flexTab").removeClass("is-block");
$(".tabs-no-border .is-active").addClass("bkimg-light");
$(".tabs-no-border>ul>li").click(function (e) {
  $(this).addClass(["is-active", "bkimg-light"]).siblings().removeClass(["is-active", "bkimg-light"]);
  let tabNow = $(".tab-contents").children().eq($(this).index());
  tabNow.addClass("is-block").siblings().removeClass("is-block");

  if ("flexTab" == tabNow.attr("id")) {
    $("#flexTab").removeClass("is-block").addClass("is-flex");
  } else {
    $("#flexTab").removeClass("is-flex");
  }
});

var heightTabScrollArea = window.innerHeight - $("#accordionExample").first().offset().top;
$("#accordionExample").css("height", heightTabScrollArea + "px");

function initBtn4Img(idBtn, imgWidth, imgHeight, imgSrc) {
  var className4img = ".btn-4img";
  $(idBtn + " " + className4img).css({
    width: imgWidth + "px",
    height: imgHeight + "px",
    "background-image": "url(" + imgSrc + ")",
    // "background-size": "355px 16px",
  });

  $(idBtn)
    .hover(
      function () {
        $(this)
          .children(className4img)
          .css("background-position", -1 * (imgWidth + 1) + "px 0px");
      },
      function () {
        $(this).children(className4img).css("background-position", "0px 0px");
      }
    )
    .mousedown(function () {
      $(this)
        .children(className4img)
        .css("background-position", -2 * (imgWidth + 1) + "px 0px");
    })
    .mouseup(function () {
      $(this)
        .children(className4img)
        .css("background-position", -1 * (imgWidth + 1) + "px 0px");
    });
}

initBtn4Img("#btn_open", 88, 16, "assets/skin/btn_open.png");
initBtn4Img("#btn_open2", 34, 40, "assets/skin/combo_open.png");
initBtn4Img("#btn_refresh", 18, 18, "assets/skin/btn_refresh.png");

initBtn4Img("#btnPlaylistShow", 18, 18, "assets/skin/btn_playlist.png");
initBtn4Img("#btnPlaylistHide", 18, 18, "assets/skin/btn_playlist_hide.png");

initBtn4Img("#btnStop", 40, 40, "assets/skin/btn_stop.png");
initBtn4Img("#btnPrevious", 40, 40, "assets/skin/btn_previous.png");
initBtn4Img("#btnPlay", 48, 48, "assets/skin/btn_play.png");
initBtn4Img("#btnPause", 48, 48, "assets/skin/btn_pause.png");
initBtn4Img("#btnNext", 40, 40, "assets/skin/btn_next.png");
initBtn4Img("#btnVolumeZero", 16, 18, "assets/skin/btn_volume.png");
initBtn4Img("#btnVolume", 16, 18, "assets/skin/btn_volume_zero.png");
initBtn4Img("#btnOpenMini", 24, 18, "assets/skin/btn_open_mini.png");
initBtn4Img("#btnScreenFull", 24, 18, "assets/skin/btn_screen_full.png");
initBtn4Img("#btnScreenNormal", 24, 18, "assets/skin/btn_screen_normal.png");

initBtn4Img("#btnPlayMode", 18, 18, "assets/skin/btn_play_mode.png");
initBtn4Img("#btnAdd", 18, 18, "assets/skin/btn_add.png");
initBtn4Img("#btnDelete", 18, 18, "assets/skin/btn_delete.png");
initBtn4Img("#btnFont", 27, 27, "assets/skin/btn_font.png");

let g_video = window.document.querySelector("#video");
// 点击切换暂停、播放
$("#video").click(function () {
  if (g_video.paused) {
    g_video.play();
  } else {
    g_video.pause();
  }
});

// 切换 显示、隐藏
function toggleRemoveClass(selector, className = "hidden") {
  if ($(selector).hasClass(className)) {
    $(selector).removeClass(className);
  } else {
    $(selector).toggle();
  }
}

function toggleElement(selector1, selector2, className = "hidden") {
  toggleRemoveClass(selector1, className);
  toggleRemoveClass(selector2, className);
}

// $("#btnPause").show(); 这个不能移除class，所以如果hidden加在class里时，这种无效
// $("#btnPause:hidden" ).show( ); 这个应该也OK 官方文档的:hidden Selector
// showByClass("#btnPause"); 这个2种情况都OK
// 在removeClass之前，不能先调.show()，否则失效
function showByClass(selector, bShow = true, className = "hidden") {
  if (bShow) {
    // $(selector).removeClass(className).show(); // 不要再加.show() 否则会导致界面闪动
    $(selector).removeClass(className);
    if ($(selector).is(":hidden")) {
      $(selector).show();
    }
  } else {
    $(selector).addClass(className); // .hide()
  }
}

function showImportant(selector, bShow = true) {
  showByClass(selector, bShow, "hiddenImportant");
}

function showVisibility(selector, bShow = true) {
  showByClass(selector, bShow, "hiddenVisibility");
}

function showUIWhenPlay() {
  showByClass(".show-when-play");
  showImportant(".showImportant-when-play");
  showVisibility(".visible-when-play");

  showImportant(".hiddenImportant-when-play", false);
  $(".hidden-when-play").hide();

  $("#playPanel").addClass("bkg-color-translucent");

  if ($("#btnScreenNormal").is(":hidden")) {
    showByClass("#btnScreenFull");
  }

  // $("#btnPlay").show();
  // $("#btnPause, #btnStop").hide();
}

async function play() {
  // g_video.src = "_movie_test.mp4";
  if (!g_video.src) return;

  try {
    await g_video.play();
  } catch (err) {
    // console.log(err);
    if (err.code != 20) {
      // 播放失败，不支持这个格式
      showModalDialog("播放失败，请换个文件! web自带只支持3种格式，本项目旨在试试electron开发界面的效果，故不做完整格式支持。\n 完整的格式支持请看duilib、或blinkUI界面库的版本！");
    }
    return;
  }

  showUIWhenPlay();
}

function playVideo(path) {
  g_video.pause();
  g_video.src = path;
  $("#sliderProgress")[0].value = 0;
  play();
}

$("#btnPlay").click(function (e) {
  play();
});

$("#btnStop").click(function (e) {
  g_video.pause();
  g_video.removeAttribute("src");
  g_video.load();

  // toggleElement("#btnPlay", "#btnStop");
  $(this).toggle();
  $("#btnPlay").show();

  showByClass(".show-when-play", false);
  showImportant(".showImportant-when-play", false);
  showVisibility(".visible-when-play", false);

  showImportant(".hiddenImportant-when-play", true);
  $(".hidden-when-play").show();

  $("#playPanel").removeClass("bkg-color-translucent");
});

$("#btnPause").click(function (e) {
  g_video.pause();
  toggleElement("#btnPlay", "#btnPause");
});

$("#btnVolumeZero").click(function (e) {
  g_video.muted = true;
  toggleElement("#btnVolumeZero", "#btnVolume");
});

$("#btnVolume").click(function (e) {
  g_video.muted = false;
  toggleElement("#btnVolumeZero", "#btnVolume");
});

// 多个id 响应同一个函数
$("#btnScreenNormal, #btnScreenFull").click(function (e) {
  ipcRenderer.send("window-event", "toggle-FullScreen");

  // $("#btnScreenFull").toggle();
  // // $("#btnScreenNormal").toggle();
  // toggleRemoveClass("#btnScreenNormal");
  toggleElement("#btnScreenFull", "#btnScreenNormal");
  $(".hidden-when-fullscreen").toggle();
});

// 多个事件 响应同一个函数 onclick oninput onchange
$("#sliderVolume").on("click input", function (event) {
  $("#btnVolume").hide();
  showByClass("#btnVolumeZero");

  g_video.muted = false;
  g_video.volume = $(this)[0].value / 100.0;
});

$("#sliderProgress").on("click input", function (event) {
  g_video.currentTime = (g_video.duration * $(this)[0].value) / 1000.0;
});

g_video.ontimeupdate = (event) => {
  if (!g_video.duration) return;

  $("#sliderProgress")[0].value = (1000.0 * g_video.currentTime) / g_video.duration;
  // console.log($("#sliderProgress")[0].value, event.timeStamp, g_video.currentTime, g_video.duration);
};

// 视频已放完
g_video.onended = (event) => {
  playNext();
};

$("#btnNext").click(function (e) {
  playNext();
});

$("#btnPrevious").click(function (e) {
  playPrev();
});

$("#btnPlaylistShow").click(function (e) {
  // $("#playlist").removeClass("hidden");
  showByClass("#playlist");
  toggleElement("#btnPlaylistShow", "#btnPlaylistHide");
});

$("#btnPlaylistHide").click(function (e) {
  $("#playlist").hide();
  toggleElement("#btnPlaylistShow", "#btnPlaylistHide");
});

var dataTreePlaylist = [
  {
    text: "迅雷下载",
    // icon: "fa fa-folder",

    expanded: true,
    nodes: [
      {
        text: "下载1",
        // icon: "fa fa-folder",
        "data-custom": "_movie_test.webm",
      },
      {
        text: "下载2",
        "data-custom": "_movie_test.mp4",
      },
    ],
  },
];

var dataTreeMedia = [
  {
    text: "今日热播",
    expanded: true,
    nodes: [
      {
        text: "斗罗大陆",
      },
      {
        text: "天龙八部",
      },
    ],
  },
];

var dataTreeMedia2 = [
  {
    text: "热点新闻",
    expanded: true,
    nodes: [
      {
        text: "八公",
      },
      {
        text: "HACHI",
      },
    ],
  },
];

var dataTreeLiveCenter = [
  {
    text: "短视频广场",
    expanded: true,
    nodes: [
      {
        text: "热门视频",
      },
      {
        text: "美女视频",
      },
    ],
  },
  {
    text: "直播频道",
  },
  {
    text: "乡村振兴",
  },
];

$("#treePlaylist").bstreeview({
  data: dataTreePlaylist,
  expandIcon: "fa-solid fa-minus",
  collapseIcon: "fa-solid fa-plus",
  parentsMarginLeft: "0rem",
});

$("#treeMedia").bstreeview({
  data: dataTreeMedia,
  expandIcon: "fa-solid fa-minus",
  collapseIcon: "fa-solid fa-plus",
  parentsMarginLeft: "0rem",
});

$("#treeMedia2").bstreeview({
  data: dataTreeMedia2,
  expandIcon: "fa-solid fa-minus",
  collapseIcon: "fa-solid fa-plus",
  parentsMarginLeft: "0rem",
});

$("#treeLiveCenter").bstreeview({
  data: dataTreeLiveCenter,
  expandIcon: "fa-solid fa-minus",
  collapseIcon: "fa-solid fa-plus",
  parentsMarginLeft: "0rem",
});

// 支持拖入文件
window.ondragover = function (e) {
  e.preventDefault();
  return false;
};

window.ondrop = function (e) {
  e.preventDefault();
  acceptFiles(e.dataTransfer.files);
  return false;
};

$("#btn_open").click(function (e) {
  $("#fileOpen").trigger("click");
});

let g_files = [];
function OnCppAddToPlaylistBegin() {
  g_files = [];
  console.log("------ OnCppAddToPlaylistBegin:");
}

function OnCppAddToPlaylistFinish() {
  console.log("------ g_files:", g_files);
  acceptFiles(g_files);
}

function OnCppAddToPlaylist(path) {
  console.log("------ path:", path);
  console.log(path);

  g_files.push(path);
}

function onNativeRunjs(msg) {
  console.log("onNativeRunjs msg:" + msg);

  return "onNativeRunjs return";
}

function onCallbackNative(customMsgID, response) {
  console.log("onCallbackNative customMsgID:" + customMsgID);
  console.log("onCallbackNative response:" + response);

  switch (customMsgID) {
    case 0x101:
      if (response) {
        let files = [response];
        // files.push(response);
        console.log("files:" + files);
        acceptFiles(files);
      }

      break;

    case 0x02:
      break;
  }
}

$("#fileOpen").click(function (e) {
  window.mbQuery(0x101, "openFileDialog", onCallbackNative);
});

// $("#fileOpen").on("change", function (event) {
//   acceptFiles($(this)[0].files);
// });

function getFileNameByPath(path) {
  var index = path.lastIndexOf("\\");
  if (-1 == index) index = path.lastIndexOf("/");
  var fileName = path.substr(index + 1);
  return fileName;
}

function acceptFiles(files) {
  showByClass("#playlist");

  if (files.length <= 0) return;
  // console.log(files);
  // console.log(files[0].path);
  // { name: "_movie_test.mp4", path: "H:\\_MyCode\\XMP-VideoPlayer-Electron\\_movie_test.mp4", size: 384193, type: "video/mp4" };

  for (var i = 0; i < files.length; i++) {
    let pathFull = files[i];
    let name = getFileNameByPath(pathFull);
    console.log(name);
    let info = {
      name: name,
      path: pathFull,
      // size: file.size,
      // type: file.type,
    };

    let json = JSON.stringify(info);
    var newRow = `<div class="list-group-item" tabindex="0" data-custom='${json}'> ${name}</div>`;
    // var newRow =  $(`<div class="list-group-item" tabindex="0" data-custom='${json}'> ${file.name}</div>`);
    // 用jQuery的$()初始化，那么没加到dom之前，就可以像dom一样操作，比如newRow.css()
    $("#treePlaylist").append(newRow);
  }

  addListenToListGroup();
  playNext(); // 拖完文件后，默认播放下一个文件
}

function addListenToListGroup() {
  $(".list-group-item").on("click", function () {
    $(".list-group-item").removeClass("active");
    $(this).addClass("active");
  });

  $("#treePlaylist .list-group-item").on("dblclick", function () {
    // console.log($(this).text());
    // console.log($(this).attr("data-custom"));
    let info;
    try {
      info = JSON.parse($(this).attr("data-custom"));
    } catch (e) {
      return true;
    }

    if (!info || !info.path) return true;
    playVideo(info.path);
  });
}

addListenToListGroup();

function playNext(bPrev = false) {
  let groupItems = $("#treePlaylist > .list-group-item");
  if (groupItems.length <= 1) return;

  let itemActive = groupItems.filter(".active");
  // var index = groupItems.index(itemActive);
  var index = itemActive.index() - 1; // 2种都行
  if (index <= 0) index = 0;

  if (!bPrev) {
    ++index;

    if (index >= groupItems.length) {
      index = 1; // 播放到最后，再从头播放。第0个不要，从第1个开始
    }
  } else {
    --index;

    if (index < 1) {
      index = groupItems.length - 1;
    }
  }

  let item = groupItems.eq(index);
  if (!item || !item.length) return;

  itemActive.removeClass("active");
  item.addClass("active");
  item.trigger("dblclick");
}

function playPrev() {
  playNext(true);
}
