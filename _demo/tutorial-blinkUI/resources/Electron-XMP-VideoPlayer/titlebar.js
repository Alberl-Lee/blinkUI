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

// 不能跟其他的重名
function onCallbackNativeTitlbar(customMsgID, response) {
  console.log("-- onCallbackNative customMsgID:" + customMsgID);
  console.log("-- onCallbackNative response:" + response);

  switch (customMsgID) {
    case 0x102:
      if (response) {
        showMaxMinImg("true" == response);
      }


      break;
  }
}

function toggleMaxMinImg() {
  // showMaxMinImg(ipcRenderer.sendSync("window-event", "is-maximized"));
  // ipcRenderer.send("window-event", "toggle-maximize");

  window.mbQuery(0x102, "is-maximized", onCallbackNativeTitlbar);
  window.mbQuery(0x102, "toggle-maximize");
}

$(".bui-btn-max").click(function (e) {
  toggleMaxMinImg();
});

$(".bui-btn-restore").click(function (e) {
  toggleMaxMinImg();
});

$(".bui-btn-min").click(function (e) {
  $(".bui-btn-min").blur();

  // ipcRenderer.send("window-event", "minimize");
  window.mbQuery(0x102, "minimize");
});

$(".bui-btn-close").click(function (e) {
  // ipcRenderer.send("window-event", "close");
  window.mbQuery(0x102, "close");
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
