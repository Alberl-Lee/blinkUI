/**
 * This file is loaded via the <script> tag in the index.html file and will
 * be executed in the renderer process for that window. No Node.js APIs are
 * available in this process because `nodeIntegration` is turned off and
 * `contextIsolation` is turned on. Use the contextBridge API in `preload.js`
 * to expose Node.js functionality from the main process.
 */
console.log("------------ hello blinkUI!1111");
// import { three3dCube } from "./three3dCube.js";
// import { three3dTiger } from "./three3dTiger.js";
// import { videoSupport } from "./video/ffmpeg-helper.js";
// import VideoServer from "./video/VideoServer";
// import { httpServerVideo } from "./video/httpServer/httpServerVideo.js";
// import './video/StreamPlayTech.js';

// 如果不是浏览器环境，才用require
function isElectron() {
  return window && window.process && window.process.type;
}

let remote, win;
var ipcRenderer;
if (isElectron()) {
  ipcRenderer = require("electron").ipcRenderer;
  remote = require("@electron/remote");
  win = remote.getCurrentWindow();
}

console.log("------------ hello blinkUI!");
// document.body.addEventListener("click", () => {
//   console.log("hello vscode!");
// });

// // 已在css文件设置
// $("html").css({
//   "overflow-y": "auto", // 自动隐藏垂直滚动条
// });

// body显示菜单，也可以指定任何元素
// 由于我的global-menu菜单是放在第一个tab的，所以切换到其他tab就不显示了，这样也是相当于指定了只有第1个tab元素才能显示右键菜单
document.body.addEventListener("contextmenu", (e) => {
  showMenu(e);
});

function showMenu(env) {
  env.preventDefault(); // 禁止浏览器的默认菜单
  var e = env || window.event; // 兼容event事件
  var x = e.clientX; // 获取鼠标的坐标
  var y = e.clientY;
  var menu = $("#global-menu");
  var menuWidth = menu.width();
  var menuHeight = menu.height();

  if (x + menuWidth > window.innerWidth) {
    x = e.clientX - menuWidth;
  }

  if (y + menuHeight > window.innerHeight) {
    y = e.clientY - menuHeight;
  }

  menu.css({ left: x + "px", top: y + "px", display: "block" });
  return false;
}

// 当鼠标点击后关闭右键菜单
document.onclick = function () {
  closeMenu();
};
function closeMenu() {
  var menu = document.getElementById("global-menu");
  menu.style.display = "none";
}

var heightTabScrollArea = window.innerHeight - $(".tabScroll").first().offset().top;
$(".tabScroll").css("height", heightTabScrollArea + "px");

function showMaxMinImg(bShowMaxImg) {
  if (bShowMaxImg) {
    $(".blk-btn-max").show();
    $(".blk-btn-restore").hide();
  } else {
    $(".blk-btn-max").hide();
    $(".blk-btn-restore").show();
  }
}

function toggleMaxMinImg() {
  showMaxMinImg(win.isMaximized());
}

$(".blk-btn-max").click(function (e) {
  // $(this).addClass("is-hidden");
  // $(this).hide();
  // $(this).toggle();
  // $(".blk-btn-max").hide();
  // $(".blk-btn-restore").show();
  toggleMaxMinImg();
  win.maximize();
});

$(".blk-btn-restore").click(function (e) {
  // $(this).hide();
  // $(".blk-btn-max").show();
  // $(".blk-btn-restore").hide();
  toggleMaxMinImg();
  win.unmaximize();
});

$(".blk-btn-min").click(function (e) {
  win.minimize();
});

$(".blk-btn-close").click(function (e) {
  win.close();
  // remote.app.quit()
});

if (isElectron()) {
  win.on("maximize", () => {
    showMaxMinImg(false);
  });

  win.on("unmaximize", () => {
    showMaxMinImg(true);
  });
}

// 标题栏按钮 禁止显示 自己的右键菜单
$(".blk-titlebar").contextmenu(function (e) {
  e.preventDefault();
  return false;
});

// mainWindow.webContents.on("did-finish-load", function () {});
// // 避免拖拽文件太快，导致electron直接换页打开拖拽的文件
// mainWindow.webContents.on("will-navigate", function (event) {
//   event.preventDefault();
// });

// window.on("did-finish-load", function () {});
// // 避免拖拽文件太快，导致electron直接换页打开拖拽的文件
// window.on("will-navigate", function (event) {
//   event.preventDefault();
// });

// 好像不需要这样搞
// //禁止窗口拖拽的默认行为
// window.ondrop =
//   window.ondrag =
//   window.ondragover =
//   window.ondragleave =
//   document.ondrag =
//   document.ondragover =
//   document.ondragleave =
//     function (e) {
//       e.preventDefault();
//       return false;
//     };
//  document.ondrop = function(e) {
//   $("#btn").ondrop = function(e) {

// 支持拖入文件
window.ondragover = function (e) {
  e.preventDefault();
  return false;
};

window.ondrop = function (e) {
  e.preventDefault();
  var files = e.dataTransfer.files;
  // 处理文件
  console.log(files);
  if (files.length > 0) {
    console.log(files[0].path);
  }
  return false;
};

// let isEnter = false;
// let isLeave = false;
// $(".dragCustom2")
//   .mouseenter(function () {
//     // $(".dragCustom2").load(location.href + " .dragCustom2"); // Reload
//     // $(".dragCustom222").load(location.href + " .dragCustom222");
//     // location.reload();

//     $(".dragCustom2").on("load", function () {
//       $(".dragCustom2").css("app-region", "drag");
//     });

//     // $(".dragCustom2").css("background-color", "yellow");

//     // $(".dragCustom2").ready(function () {
//     //   $(".dragCustom2").css("app-region", "drag");
//     // });

//     // $(".dragCustom2").load(location.href + " .dragCustom2"); // Reload
//     // load之后恢复到HTML的初始状态了，得重新js设置属性
//     // $(".dragCustom2").reload();

//     // app-region属性用js动态设置不生效，除非同时打开F12，并且要把右侧的HTML展开到显示出本元素的HTML，才生效，此时才能拖动。。。
//     // $(".dragCustom2").css("app-region", "drag"); // 只设置这个也是OK的，因为chrome自带这个属性
//     // $(".dragCustom2").css("-webkit-app-region", "drag"); // jquery的bug，调用这个后，变成了app-region，不过获取-webkit-app-region也是对的，说明把-webkit-去掉了
//     // $(".dragCustom2").css("--webkit-app-region", "drag");  // CSS规范是自定义属性要以-- 开头，这个设置就OK
//     // $(".dragCustom2").css("webkitappregion", "drag"); // 这个也设置不成功，没有这个属性

//     // $(".dragCustom2").css({ "app-region": "drag", "-webkit-app-region": "drag" });
//     // $(".dragCustom2").removeClass("no-dragable");
//     // $(".dragCustom2").addClass("dragable");

//     // let a = $(".dragCustom2").css("app-region");
//     // let d =  $(".dragCustom2").css("-webkit-app-region");
//     // $(".dragCustom2").css("app-region", "drag");
//     // $(".dragCustom2").css("-webkit-app-region", "drag");
//     // d =  $(".dragCustom2").css("-webkit-app-region");
//     // a = $(".dragCustom2").css("app-region");
//     // $(".dragCustom2").addClass("dragable"); // 用css addClass设置同一个属性，是css生效，addClass不生效
//     // $(".foreground").addClass("no-select");
//     // $(".dragCustom2").attr("style", "-webkit-app-region: drag; background-color: pink; ");
//     // document.getElementById("aa").style.cssText = "-webkit-app-region: drag";
//     // 原生js设置-webkit-app-region也变成app-region
//     // 不过下面这个没有变
//     $(".dragCustom2").get(0).setAttribute("style", "-webkit-app-region: drag; background-color: pink; ");
//     // $(".dragCustom2").get(0).setAttribute("style", "-webkit-app-region: drag");

//     $(".dragCustom2").click(function () {
//       $(".dragCustom2").get(0).setAttribute("style", "-webkit-app-region: drag; background-color: red; ");
//     });

//     // 点一下任务栏，把窗口最小化，然后再点一下，恢复后，就可以拖拽了，说明这个要重载？ 或者触发什么消息？
//     // 切换tab也生效，这个是block hidden切换了，应该是这段dom重新加载了  滚动条滚动出去再回来，也生效。滚动只要有一部分区域不显示，就生效
//     //滚动条随便滚动一下就行了，但是点击内部的按钮，却没用，说明不是重绘事件，scroll要触发display？
//     // 是onblur事件？
//     // $(".dragCustom2").trigger("resize");
//     $(".dragCustom2").trigger("click");
//     $(".dragCustom2").trigger("scroll");
//     $(".dragCustom222").trigger("scroll");
//     $(document).trigger("scroll");
//     // $(body).trigger("scroll");
//     $(window).trigger("resize");
//     $(window).trigger("scroll");

//     //
//     //----------是因为有这个css代码，导致不能立即生效，注释掉就正常了
//     // button .button { -webkit-app-region: no-drag; // 按钮区域不允许拖拽，否则无法点击}

//     //  display: flex !important;
//     // $(".dragCustom2").css("display", "none");
//     // $(".dragCustom2").css("display", "none !important");
//     // $(".dragCustom2").css("display", "none");
//     // $(".dragCustom2").css("display", "block");

//     // $('.dragCustom2').attr('style','display:none !important');
//     // $(".dragCustom2").attr("style", "display:flex !important; -webkit-app-region: drag; background-color: pink; ");
//     $(".dragCustom2").css("cssText", "display:none !important");
//     $(".dragCustom2").css("cssText", "display:flex !important; -webkit-app-region: drag; background-color: pink; ");

//     console.log("------------------mouseenter ");
//     isEnter = true;
//     isLeave = false;
//   })
//   .mouseleave(function () {
//     console.log("------------------mouseleave ");
//     // $(".dragCustom2").css("-webkit-app-region", "no-drag");
//     isEnter = false;
//     isLeave = true;
//   })
//   .mouseover(function () {
//     // $(".dragCustom2").css("background-color", "red");
//     console.log("------------------mouseover ");
//   })
//   .mouseout(function (e) {
//     // e.currentTarget.style.backgroundColor ='blue';
//     // const target = e.target;
//     // switch (target.id) {
//     //   case "div1":
//     //     target.style.backgroundColor = "blue";
//     //     break;
//     //   case "div2":
//     //     target.style.backgroundColor = "green";
//     //     break;
//     //   case "div3":
//     //     target.style.backgroundColor = "red";
//     //     break;
//     // }
//     // console.log(target.id);
//     // console.log(target);

//     // let me2 = $(".dragCustom2").first(); // jQuery对象
//     let me = $(".dragCustom2").get(0); // dom对象
//     if (e.target == me) {
//       console.log("My event"); // mouseout 离开了父元素，进入了子元素
//       // $(".dragCustom2").css("background-color", "green");
//     } else {
//       console.log("Child event"); // mouseout 离开了子元素，进入了父元素
//       // $(".dragCustom2").css("background-color", "blue");
//     }

//     if (isLeave) {
//       // $(".dragCustom2").css("background-color", "lightgray");

//       console.log("isLeave mouseout ");
//       return true;
//     }
//     // $(".dragCustom2").css("background-color", "green");
//     console.log("------------------mouseout ");

//     // 如果鼠标在自己身上，不在子元素身上，则允许拖动
//   });

// // ---------窗口拖拽
// let isDraging = false;
// let xOld = 0,
//   yOld = 0;

// function dragBegin() {
//   isDraging = true;
//   $(".dragCustom").addClass("no-select");

//   if (window.captureEvents) {
//     window.captureEvents(Event.MOUSEMOVE | Event.MOUSEUP);
//   }
// }

// function dragEnd() {
//   isDraging = false;

//   if (window.captureEvents) {
//     window.releaseEvents(Event.MOUSEMOVE | Event.MOUSEUP);
//   }

//   $(".dragCustom").removeClass("no-select");
// }

// $(document).mouseup(function (e) {
//   console.log("------------------document mouseup: ");

//   dragEnd();
// });

// $(document).mouseleave(function (e) {
//   console.log("------------------document mouseleave: ");

//   dragEnd();
// });

// $(document).mouseout(function (e) {
//   dragEnd();
// });

// $(".dragCustom").mouseup(function (e) {
//   dragEnd();

//   // console.log("------------------mouseup: ");
// });

// $(".dragCustom").mouseleave(function (e) {
//   dragEnd();

//   // console.log("------------------mouseleave: ");
//   // dragEnd();
// });

// let timeOld = 0;

// $(".dragCustom").mousedown(function (e) {
//   // console.log("------------------mousedown: ");

//   dragBegin();
//   xOld = e.screenX;
//   yOld = e.screenY;
// });

// $(".dragCustom").mousemove(function (e) {
//   if (!isDraging) return;
//   let timeNow = new Date().getTime();
//   let interval = timeNow - timeOld;
//   // console.log("timeNow " + timeNow + "  interval " + interval);

//   // if (interval < minInterval) return;
//   // timeOld = timeNow;

//   // console.log("mousemove: ");

//   const remote = require("@electron/remote");
//   const win = remote.getCurrentWindow();
//   let x = e.screenX;
//   let y = e.screenY;
//   let display = remote.screen.getDisplayNearestPoint({ x, y });
//   let screenScale = display.scaleFactor;
//   let xOffset = e.screenX - xOld;
//   let yOffset = e.screenY - yOld; // 这个也没有*1.25
//   xOld = e.screenX;
//   yOld = e.screenY;

//   if (screenScale != 1) {
//     // 能被 1/(screenScale-1)整除，就不会有问题
//     let integerDPI = 1 / (screenScale - 1);
//     let remainX = xOffset % integerDPI;
//     let remainY = yOffset % integerDPI;

//     if (0 != remainX) {
//       // 解决移动过程中，鼠标不太跟窗口的问题  1/(screenScale-1)
//       // if (xOffset < 0) {
//       //   // xOffset+=1;
//       //   // xOffset+=2;
//       //   xOffset += 1 + -Math.round(remain / integerDPI);
//       // } else if (xOffset > 0) {
//       //   xOffset += 1 + Math.round(remain / integerDPI);
//       // }

//       xOffset += 1 + Math.abs(Math.round(remainX / integerDPI));
//     }

//     if (0 != remainY) {
//       yOffset += 1 + Math.abs(Math.round(remainY / integerDPI));
//     }

//     // console.log("xOffset: " + xOffset + ", yOffset: " + yOffset);
//   }

//   // ipcRenderer.send("move-application", {
//   //   xOffset: xOffset,
//   //   yOffset: yOffset,
//   // });

//   // 不用ipc，可以直接remote访问
//   const pos = win.getPosition(); //  这个也没有*1.25
//   pos[0] += xOffset;
//   pos[1] += yOffset;
//   // console.log(win.getBounds());
//   if (screenScale == 1) {
//     win.setPosition(pos[0], pos[1], true); // true Mac才有动画效果
//     return;
//   }

//   let bounds = win.getBounds();
//   let workAreaSize = remote.screen.getPrimaryDisplay().workAreaSize;
//   // const displayWorkAreaSize = remote.screen.getAllDisplays()[0].workArea
//   const displayWorkAreaSize = remote.screen.getPrimaryDisplay().workArea;
//   // win.setBounds({ width: workAreaSize.width, height: workAreaSize.height }); // 多调一次修正
//   // screen.screenToDipRect(window, rect) Windows

//   const WIDTH = 1200;
//   const HEIGHT = 800;
//   // x=164是对的  166就变成165 width: 1202
//   // x=100 是对的，set后还是 100  1200
//   // x=101 是错的，就变成  x:100  width: 1202
//   // scale = 1.25    scale = 1.5      setBounds({width: WIDTH, height: HEIGHT })    resizable: false
//   //                                  纠正，每纠正一次，就是往前-1个像素点
//   // x   x   width   x   width        x   width                                     x   width
//   // 100 100 1200  √  100 1200   √
//   // 101 100 1202    100 1202         100 1200   √
//   // 102 101 1202    102 1200   √     100 1202
//   // 103 102 1202    102 1202         101 1202
//   // 104 104 1200  √  104 1200   √
//   // 105 104 1202    104 1202         104 1200   √
//   // 106 105 1202    106 1200   √     104 1202
//   // 107 106 1202    106 1202         105 1202
//   // 108 108 1200  √  108 1200   √
//   // 109 108 1202    108 1202         108 1200   √
//   // 110 109 1202    110 1200   √     108 1202
//   // 111 110 1202    110 1202         109 1202
//   // 112 112 1200  √  112 1200   √
//   // 113 112 1202    112 1202         112 1200   √
//   // x都是差-1    width都是差+2。 因为这些都是/scale了。 第1个x是屏幕像素100  第2个x是被*scale绘制到屏幕上，但getBounds会再/scale
//   // x的误差问题不大，差1个像素，移动过程肉眼看不出来。
//   // 而且x被缩放后，本身就会差1个像素，是因为没有半个像素点，只能向下取整，这个解决不了，除非DPI设置为1的整数，比如200%，但一般客户都是设置为125% 115%。
//   // 而width就会影响布局，元素老是变，所以把width恢复一下就行。
//   // 1.25时，x能被4整除的，就正确。  1.5时，能被2整除的，就正确。 说明是能被1/(scale-1) 整除，就正确。  而且不管x怎么设置，缩放后的x，尾数都没出现3 7 11 13 17的
//   // 不好解决，主要是setBounds会自动缩放*1.25，如果能自己去调用更底层的，就能解决。这个不是electron的问题，是chromium的bug，除非再改改chromium
//   // 加上  resizable: false能解决，但是窗口不能调节大小了。  不过，可以拖拽前设置为false，拖拽后，设置为true恢复原来的状态
//   // resizable: false 依然有误差 width都是差+1
//   let resizableOld = win.isResizable();
//   win.setResizable(false);

//   // // win.setPosition(pos[0], pos[1], true); // true Mac才有动画效果
//   // // win.setSize(sizeOld[0], sizeOld[1]); // DPI不等于100%时，setPosition会改变大小，所以要setSize恢复一下，会有2个像素的误差，是计算精度问题
//   // win.setBounds({ x: pos[0], y: pos[1], width: WIDTH, height: HEIGHT });
//   // // console.log(win.getBounds());
//   // win.setBounds({ width: WIDTH, height: HEIGHT }); // 跟setSize效果一样
//   // win.setBounds({ width: WIDTH, height: HEIGHT }); // 多调一次修正
//   // // console.log(win.getBounds());

//   // win.setResizable(true);
//   win.setResizable(resizableOld);
// });

// // ---chatGPT 给出的：electron实现窗口全局拖拽
// // 获取当前窗口
// const remote = require("@electron/remote");
// let win = remote.getCurrentWindow();

// // 监听鼠标按下事件
// document.addEventListener("mousedown", (e) => {
//   // 获取鼠标按下时的坐标
//   let x = e.clientX;
//   let y = e.clientY;
//   // 监听鼠标移动事件
//   document.addEventListener("mousemove", (e) => {
//     // 计算窗口移动的距离
//     let moveX = e.clientX - x;
//     let moveY = e.clientY - y;
//     // 获取当前窗口的位置
//     let position = win.getPosition();
//     // 设置窗口新的位置
//     win.setPosition(position[0] + moveX, position[1] + moveY);
//   });
// });

// // 监听鼠标松开事件
// document.addEventListener("mouseup", () => {
//   // 移除鼠标移动事件
//   document.removeEventListener("mousemove", () => {});
// });

// // Dropdowns
// var $dropdowns = getAll(".dropdown:not(.is-hoverable)");

// if ($dropdowns.length > 0) {
//   $dropdowns.forEach(function ($el) {
//     $el.addEventListener("click", function (event) {
//       event.stopPropagation();
//       $el.classList.toggle("is-active");
//     });
//   });

//   document.addEventListener("click", function (event) {
//     closeDropdowns();
//   });
// }

// function closeDropdowns() {
//   $dropdowns.forEach(function ($el) {
//     $el.classList.remove("is-active");
//   });
// }

// // Utils
// function getAll(selector) {
//   var parent = arguments.length > 1 && arguments[1] !== undefined ? arguments[1] : document;

//   return Array.prototype.slice.call(parent.querySelectorAll(selector), 0);
// }

// dropdown JQuery代码：简化很多
$(".dropdown-trigger").click(function (e) {
  e.preventDefault();
  $(this).parent(".dropdown").toggleClass("is-active");
});

// 只响应id = btnDropdown
// $("#btnDropdown").blur(function () {
//   $(this).parent().parent().removeClass("is-active");
// });

// 这个比上面的更通用，把所有的dropdown都隐藏
// 1 只有button edit等元素才能响应blur
// 2 而且只有自己失去焦点时，才会触发blur
// $(".dropdown-trigger button").blur(function () {
//   $(this).parent().parent().removeClass("is-active");
// });

// 1 div等任何元素都能响应focusout
// 2 自己或子元素失去焦点时，都会触发focusout
$(".dropdown").focusout(function () {
  $(this).removeClass("is-active");
});

// // 模态框 原生JS
// document.addEventListener("DOMContentLoaded", () => {
//   // Functions to open and close a modal
//   function openModal($el) {
//     $el.classList.add("is-active");
//   }

//   function closeModal($el) {
//     $el.classList.remove("is-active");
//   }

//   function closeAllModals() {
//     (document.querySelectorAll(".modal") || []).forEach(($modal) => {
//       closeModal($modal);
//     });
//   }

//   // Add a click event on buttons to open a specific modal
//   (document.querySelectorAll(".js-modal-trigger") || []).forEach(($trigger) => {
//     const modal = $trigger.dataset.target;
//     const $target = document.getElementById(modal);

//     $trigger.addEventListener("click", () => {
//       openModal($target);
//     });
//   });

//   // Add a click event on various child elements to close the parent modal
//   (document.querySelectorAll(".modal-background, .modal-close, .modal-card-head .delete, .modal-card-foot .button") || []).forEach(($close) => {
//     const $target = $close.closest(".modal");

//     $close.addEventListener("click", () => {
//       closeModal($target);
//     });
//   });

//   // Add a keyboard event to close all modals
//   document.addEventListener("keydown", (event) => {
//     const e = event || window.event;

//     if (e.keyCode === 27) {
//       // Escape key
//       closeAllModals();
//     }
//   });
// });

// 模态框 JQuery代码：简化很多
$(document).ready(function () {
  $(".modal-close, .modal-background, .delete").click(function () {
    $(this).parent(".modal").removeClass("is-active"); // 只关闭目前的
    // $(".modal").removeClass("is-active"); // 关闭所有模态框
  });

  $(".js-modal-trigger").click(function () {
    // alert($(this).data("target"));
    var id = $(this).data("target"); // HTML5新属性data-target
    $("#" + id).addClass("is-active");
    // $(":root").toggleClass("is-clipped");
  });
});

// delete图标样式的响应
$(".tag .delete").click(function (e) {
  $(this).parent(".tag").remove();
});

$(".notification .delete").click(function (e) {
  $(this).parent(".notification").remove();
});

$(".message .delete").click(function (e) {
  $(this).parents(".message").remove();
});

// 用JQuery自己处理tabs的click事件
$(".tabs>ul>li").click(function (e) {
  // e.preventDefault();
  $(this).addClass("is-active").siblings().removeClass("is-active");
  $(this).parents(".tabs").next().children().eq($(this).index()).addClass("is-block").siblings().removeClass("is-block");
  // 这里移除和添加了is-block，所以animate动画才会响应，相当于先隐藏后，再重新显示了。 .is-block {  display: block !important; }
});

// JQuery UI现成的tabs。 但是跟bulma不兼容，内容是放到tabs里面，但bulma是跟tabs同级。所以这个tabs不能融合只能二选一，显然风格更重要，自己再用上面的js就行了
// 把上面的bulma js代码改了，就可以跟JQuery UI兼容了 $(this).parents(".tabs").next().
// 不过bulma的更合理，因为tab跟tabcontent平级，可以把它挤下去，两者不公用父元素分开之后，也更方便调整布局，一般tab是水平、content是垂直
var tabs = $("#tabsJQueryUI").tabs();
// tabs可拖拽
var previouslyFocused = false;
tabs.find(".ui-tabs-nav").sortable({
  axis: "x",

  // Sortable removes focus, so we need to restore it if the tab was focused
  // prior to sorting
  start: function (event, ui) {
    previouslyFocused = document.activeElement === ui.item[0];
  },
  stop: function (event, ui) {
    tabs.tabs("refresh");
    if (previouslyFocused) {
      ui.item.trigger("focus");
    }
  },
});

// bulmaCollapsible.attach();
// bulmaCarousel.attach();
// bulmaCarousel.attach({
//   slidesToScroll: 1,
//   slidesToShow: 3,
//   // autoplay:true
// });

// 可拖拽排序  要加上class="group"属性，并且改变div布局，不兼容bluma的css,但是包装一下bluma的应该可以
// 搞定了，调整下函数调用顺序，把accordion({ icons: icons });放到最后，然后removeClass("ui-icon");
$("#accordion2")
  .accordion({
    header: "> div > h3",
    // header: "h3",
  })
  .sortable({
    axis: "y",
    handle: "h3",
    stop: function (event, ui) {
      // IE doesn't register the blur when sorting
      // so trigger focusout handlers to remove .ui-state-focus
      ui.item.children("h3").triggerHandler("focusout");

      // Refresh accordion to handle new order
      $(this).accordion("refresh");
      $(".ui-icon").removeClass("ui-icon"); // JQuery UI会操作css，所以要重置一下
    },
  });

// JQuery UI的图标，是css生成的
// var icons = {
//   header: "ui-icon-circle-arrow-e",
//   activeHeader: "ui-icon-circle-arrow-s",
// };
//
// bulma的图标
var icons = {
  header: "fa-solid fa-caret-right",
  activeHeader: "fa-solid fa-caret-down",
};
// $("#accordion2").accordion(); // 默认样式，不可拖拽排序
// $("#accordion2").accordion({ icons: icons }); // 启动后,就不能改图标了
// $("#accordion2").accordion("option", "icons", icons); // 启动后,也可以改图标

$("#accordion2").accordion({
  icons: icons,
  collapsible: true, // 是否全部可折叠（此时点击自身也可折叠），默认为false（此时点击自身只可展开，不可折叠）
}); // 这句必须放到最后，否则样式会混乱
$(".ui-icon").removeClass("ui-icon"); // 删除JQuery UI的所有图标，这样bulma的图标才能生效

// one代表只进来一次，也就是初始化的时候进来一次就行了
$("#tabTabs").one("click", function () {
  $("#accordion2").accordion("option", "heightStyle", "auto");
  $("#accordion2").accordion("refresh");

  bulmaCollapsible.attach();
});

// bulmaAccordion.attach("#accordion3"); // accordions now contains an array of all Accordion instances
// bulmaTagsinput.attach("#tagsinput");
// BulmaTagsInput.attach();

// bulmaCarousel.attach("#carousel-demo", {
//   slidesToScroll: 1,
//   slidesToShow: 4,
// });

// Initialize all elements with carousel class.
// const carousels = bulmaCarousel.attach(".carousel", options);

// // To access to bulmaCarousel instance of an element
// const element = document.querySelector("#carousel-demo");
// if (element && element.bulmaCarousel) {
//   // bulmaCarousel instance is available as element.bulmaCarousel
//   element.bulmaCarousel.on("show", function (bulmaCarouselInstance) {
//     console.log(bulmaCarouselInstance.index);
//   });
// }

// bulmaCollapsible.attach("#collapsible-card");

// bulmaAccordion.attach("#accordion3");
// bulmaCarousel.attach("#slider", {
//   slidesToScroll: 1,
//   slidesToShow: 4,
// });

// bulmaCarousel.attach("#carousel-demo", {
//   slidesToScroll: 1,
//   slidesToShow: 4,
// });

// // Initialize all elements with carousel class.
// const carousels = bulmaCarousel.attach(".carousel", options);

// // To access to bulmaCarousel instance of an element
// const element = document.querySelector("#slider");
// if (element && element.bulmaCarousel) {
//   // bulmaCarousel instance is available as element.bulmaCarousel
// }

function onCallbackNative(customMsgID, response) {
  console.log("onCallbackNative customMsgID:" + customMsgID);
  console.log("onCallbackNative response:" + response);
}

let mapGridBtn = {
  btnGridURL: "https://bulma.io/documentation/elements/button/",
  btnGridCalc: "calc.exe",
  btnGridDiskC: "C:\\Program Files",
  btnGridRemoteDesktop: "mstsc.exe",
  btnGridChrome: "chrome.exe",
  btnGridFirefox: "firefox.exe",
  btnGridCmd: "cmd.exe",
  btnGridNotepad: "notepad.exe",
  btnGridRegedit: "regedit.exe",
  btnGridElectron: "https://www.electronjs.org/zh/",
  btnGridGithub: "https://github.com/",
};

var shellCache = null;
$(".blk-btn-group button").click(function (e) {
  let id = $(this).attr("id");
  if (undefined == id || "" == id) return;

  // let customMsgID = 0x003;
  // let msgName = "test run"
  // window.mbQuery(customMsgID, msgName, onCallbackNative);
  window.mbQuery(0x01, mapGridBtn[id]);

  if (!shellCache) {
    const { shell } = require("electron");
    shellCache = shell;
  }

  shellCache.openPath(mapGridBtn[id]);
  // 还可以用下面这个，不过跨平台不知道是否生效，比如mac linux
  // const { exec } = require("child_process");
  // exec("shutdown /s /t 600");
});

document.addEventListener("visibilitychange", function () {
  let pageVisibility = document.visibilityState;
  // 页面变为不可见时触发
  if (pageVisibility == "hidden") {
    // console.log("离开时间点：" + new Date());
  }
  // 页面变为可见时触发
  if (pageVisibility == "visible") {
    // console.log("重新进入时间点：" + new Date());
  }
});

// $("#test_hidden").hideShow(function (e, visibility) {
//   alert("Element hideShow " + visibility);
//   console.log(e, visibility);
// });

$("#test_hidden").hideShow();
$("#test_hidden").on("visibilityChanged", function (event, visibility) {
  alert("Element visibilityChanged " + visibility);
  console.log(visibility);
});

$("#toggle_visiblity").click(function () {
  var visible = $("#test_hidden").is(":visible");
  // console.log($("#test_hidden")["show"]())
  $("#test_hidden")[visible ? "hide" : "show"]();
});

// // 3D 老虎SVG
// three3dTiger.init();
// three3dCube.init();

// $("#three3dTiger").hideShow();
// $("#three3dTiger").on("visibilityChanged", function (event, visibility) {
//   // if ("shown" == visibility) {
//   //   $("#three3dCube").show();
//   // } else {
//   //   $("#three3dCube").hide();
//   // }

//   // 3D 正方体动画
//   three3dCube.animate("shown" == visibility);

//   console.log(visibility);
// });

$(document).ready(function () {
  // onVideoFileSeleted("assets/formatTest/movie/movie.mov");
  // onVideoFileSeleted("http://vjs.zencdn.net/v/oceans.mp4");
  // onVideoFileSeleted("G:/movie.webm");
});
