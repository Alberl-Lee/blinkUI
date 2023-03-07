// var ipcRenderer = require("electron").ipcRenderer;
// ipcRenderer.on("window-maximize", (event, param) => {
//   showMaxMinImg(param);
// });

function showMaxMinImg(bShowMaxImg) {
  if (bShowMaxImg) {
    $(".bui-btn-max").show();
    $(".bui-btn-restore").hide();
  } else {
    $(".bui-btn-max").hide();
    $(".bui-btn-restore").show();
  }
}

function toggleMaxMinImg() {
  showMaxMinImg(ipcRenderer.sendSync("window-event", "is-maximized"));
  ipcRenderer.send("window-event", "toggle-maximize");
}

$(".bui-btn-max").click(function (e) {
  toggleMaxMinImg();
});

$(".bui-btn-restore").click(function (e) {
  toggleMaxMinImg();
});

$(".bui-btn-min").click(function (e) {
  $(".bui-btn-min").blur();

  ipcRenderer.send("window-event", "minimize");
});

$(".tt").click(function (e) {
  ipcRenderer.send("window-event", "minimize");
});

$(".bui-btn-close").click(function (e) {
  ipcRenderer.send("window-event", "close");
});

$(window).on("focus", (event) => {
  onWindowFocus(true);
});

$(window).on("blur", (event) => {
  onWindowFocus(false);
});

function onWindowFocus(isFocused) {
  if (isFocused) {
    // 下面2种方法都行。 但是第1种，需要去掉 &:hover &:not(.nohover):hover代码才行。所以还是第2种方法好，不受代码影响
    // $(".bui-btn-min").addClass("is-not-hovered");
    $(".bui-btn-min").addClass("nohover");
  }
}

$(".bui-btn-min").hover(function () {
  // $(".bui-btn-min").removeClass("is-not-hovered");
  $(".bui-btn-min").removeClass("nohover");
});
