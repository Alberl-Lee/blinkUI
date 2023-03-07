// Modules to control application life and create native browser window
const { app, BrowserWindow, ipcMain } = require("electron");
const path = require("path");

function createWindow() {
  // Create the browser window.
  const mainWindow = new BrowserWindow({
    width: 968 * 1.25,
    height: 600 * 1.25,
    frame: false,

    webPreferences: {
      preload: path.join(__dirname, "preload.js"),
      nodeIntegration: true, // 在此render进程中启用node
      contextIsolation: false, // 取消上下文隔离
    },
  });

  // and load the index.html of the app.
  mainWindow.loadFile("index.html");

  // Open the DevTools.
  // mainWindow.webContents.openDevTools()
  initTitlebar(mainWindow);
}

// This method will be called when Electron has finished
// initialization and is ready to create browser windows.
// Some APIs can only be used after this event occurs.
app.whenReady().then(() => {
  createWindow();

  app.on("activate", function () {
    // On macOS it's common to re-create a window in the app when the
    // dock icon is clicked and there are no other windows open.
    if (BrowserWindow.getAllWindows().length === 0) createWindow();
  });
});

// Quit when all windows are closed, except on macOS. There, it's common
// for applications and their menu bar to stay active until the user quits
// explicitly with Cmd + Q.
app.on("window-all-closed", function () {
  if (process.platform !== "darwin") app.quit();
});

// In this file you can include the rest of your app's specific main process
// code. You can also put them in separate files and require them here.
function initTitlebar(win) {
  ipcMain.on("window-event", (event, eventName) => {
    const window = BrowserWindow.fromWebContents(event.sender);
    switch (eventName) {
      case "minimize":
        window.minimize();
        break;
      case "toggle-maximize":
        window.isMaximized() ? window.unmaximize() : window?.maximize();
        break;
      case "close":
        window.close();
        break;
      case "toggle-FullScreen":
        window.isFullScreen() ? window.setFullScreen(false) : window?.setFullScreen(true);
        break;
      case "is-maximized":
        event.returnValue = window.isMaximized();
        break;
      default:
        break;
    }
  });

  win.on("maximize", () => {
    win.webContents.send("window-maximize", false);
  });

  win.on("unmaximize", () => {
    win.webContents.send("window-maximize", true);
  });
}
