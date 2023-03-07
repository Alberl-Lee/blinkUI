/**
 * The preload script runs before. It has access to web APIs
 * as well as Electron's renderer process modules and some
 * polyfilled Node.js functions.
 *
 * https://www.electronjs.org/docs/latest/tutorial/sandbox
 */
// ipcRenderer.send 渲染进程 使用 主进程的函数
// const { contextBridge, ipcRenderer } = require("electron");
// contextBridge.exposeInMainWorld("electron", {
//   init: (window, document) => ipcRenderer.send("init-test",window, document),
// });

// // ipcRenderer.on 主进程 使用 渲染进程的函数
// const { contextBridge, ipcRenderer } = require('electron')
// contextBridge.exposeInMainWorld('electronAPI', {
//   init: (callback) => ipcRenderer.on('update-counter', callback)
// })


window.addEventListener("DOMContentLoaded", () => {
  const replaceText = (selector, text) => {
    const element = document.getElementById(selector);
    if (element) element.innerText = text;
  };

  for (const type of ["chrome", "node", "electron"]) {
    replaceText(`${type}-version`, process.versions[type]);
  }
});
