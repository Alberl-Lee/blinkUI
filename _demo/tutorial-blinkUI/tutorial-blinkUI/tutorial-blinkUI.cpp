// tutorial-blinkUI.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "tutorial-blinkUI.h"
#include <string>
#include <vector>
#include <algorithm>
#include <commdlg.h>
#include <shellapi.h>
#include <shlwapi.h>
#pragma comment(lib, "shlwapi.lib")
#include "../../../mbvip/core/mb.h"

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名
mbWebView g_windowXMP = NULL;

const TCHAR STR_FILE_FILTER[] =
_T("Movie Files(*.mp4,*.mov,etc)\0*.mp4;*.mov;*.ogg;\0")
_T("Music Files\0*.mp3;\0")
_T("All Files(*.*)\0*.*\0");

// 文件查找 
// 由于STR_FILE_FILTER有\0，所以不能用于查找，这里把\0换成|
const TCHAR STR_FILE_MOVIE[] =
_T("Movie Files(*.mp4,*.mov,etc)|*.mp4;*.mov;*.ogg;");

const TCHAR STR_FILE_MUSIC[] =
_T("Music Files|*.mp3;");


// 此代码模块中包含的函数的前向声明:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

std::string UnicodeConvert(const std::wstring& strWide, UINT uCodePage)
{
    std::string strANSI;
    int iLen = ::WideCharToMultiByte(uCodePage, 0, strWide.c_str(), -1, NULL, 0, NULL, NULL);

    if (iLen > 1)
    {
        strANSI.resize(iLen - 1);
        ::WideCharToMultiByte(uCodePage, 0, strWide.c_str(), -1, &strANSI[0], iLen, NULL, NULL);
    }

    return strANSI;
}

std::string UnicodeToUTF8(const std::wstring& strWide)
{
    return UnicodeConvert(strWide, CP_UTF8);
}

std::string UnicodeToANSI(const std::wstring& strWide)
{
    return UnicodeConvert(strWide, CP_ACP);
}


bool FindFileExt(LPCTSTR pstrPath, LPCTSTR pstrExtFilter)
{
    if (!pstrPath || !pstrExtFilter)
    {
        return false;
    }

    TCHAR szExt[_MAX_EXT] = _T("");

    _tsplitpath_s(pstrPath, NULL, 0, NULL, 0, NULL, 0, szExt, _MAX_EXT);
    _tcslwr_s(szExt, _MAX_EXT);

    if (_tcslen(szExt))
    {
        _tcscat_s(szExt, _MAX_EXT, _T(";"));    // .mo不符合条件，由于会匹配到.mov，所以在后面加上【;】来判断是否完全匹配
        return NULL != _tcsstr(pstrExtFilter, szExt);
    }

    return false;
}

bool IsMusicFile(LPCTSTR pstrPath)
{
    return FindFileExt(pstrPath, STR_FILE_MUSIC);
}

bool IsMovieFile(LPCTSTR pstrPath)
{
    return FindFileExt(pstrPath, STR_FILE_MOVIE);
}

bool IsWantedFile(LPCTSTR pstrPath)
{
    return IsMusicFile(pstrPath) || IsMovieFile(pstrPath);
}

void EnumerateFiles(std::vector<std::wstring>& vctString)
{
    WIN32_FIND_DATA fd;
    HANDLE hFind = ::FindFirstFile(_T("*.*"), &fd);

    if (hFind != INVALID_HANDLE_VALUE)
    {
        do
        {
            // 如果为目录
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if (_tcscmp(fd.cFileName, _T(".")) && _tcscmp(fd.cFileName, _T("..")))
                {
                    ::SetCurrentDirectory(fd.cFileName);
                    EnumerateFiles(vctString);
                    ::SetCurrentDirectory(_T(".."));
                }
            }
            // 如果为文件
            else
            {
                std::wstring strDir;
                TCHAR      lpDir[MAX_PATH];

                ::GetCurrentDirectory(MAX_PATH, lpDir);
                strDir = lpDir;
                if (strDir.back() != _T('\\'))
                {
                    strDir += _T("\\");
                }
                strDir += fd.cFileName;

                vctString.push_back(strDir);
            }
        } while (::FindNextFile(hFind, &fd));

        ::FindClose(hFind);
    }
}

void MB_CALL_TYPE onRunJs(mbWebView webView, void* paramCPP, mbJsExecState es, mbJsValue v)
{
    // mbJsType  kMbJsTypeNumber kMbJsTypeV8Value ...
    const utf8* str = mbJsToString(es, v);

    OutputDebugStringA("onRunJs:");
    OutputDebugStringA(str);
    OutputDebugStringA("\n");
}

void RunJs(const std::string&strScript, void* paramCPP = NULL) {
    //void* param = (void*)3;
    //mbRunJs(g_window, mbWebFrameGetMainFrame(g_window), "return window.onNativeRunjs('-------I am runjs');", TRUE, onRunJs, param, nullptr);
    //mbRunJs(g_window, mbWebFrameGetMainFrame(g_window), "return onNativeRunjs('-------I am runjs');", TRUE, onRunJs, param, nullptr);
    mbRunJs(g_windowXMP, mbWebFrameGetMainFrame(g_windowXMP), strScript.c_str(), TRUE, onRunJs, paramCPP, nullptr);
}

void AddFiles(const std::vector<std::wstring>& vctString)
{
    std::vector<std::wstring> vctPath;
    std::string  strTmp, strPath;
    TCHAR       szName[_MAX_FNAME];
    TCHAR       szExt[_MAX_EXT];
    unsigned    i, uWantedCount;

    RunJs("OnCppAddToPlaylistBegin();");

    for (i = 0; i < vctString.size(); i++)
    {
        if (IsWantedFile(vctString[i].c_str()))
        {
            vctPath.push_back(vctString[i]);
            strPath = UnicodeToANSI(vctString[i]);
            std::replace(strPath.begin(), strPath.end(), '\\', '/');
            strTmp = "OnCppAddToPlaylist('" + strPath + "');";
            RunJs(strTmp);
        }
    }

    if (vctPath.empty()) {
        ::MessageBox(NULL, L"本次文件没有能播放的格式！请更换文件！", L"格式问题", MB_OK);
        return;
    }

    //AddToPlaylist(vctPath);
    RunJs("OnCppAddToPlaylistFinish();");
}

void OnDropFiles(HWND hwnd, HDROP hDropInfo)
{
    UINT  nFileCount = ::DragQueryFile(hDropInfo, (UINT)-1, NULL, 0);
    TCHAR szFileName[_MAX_PATH] = _T("");
    DWORD dwAttribute;
    std::vector<std::wstring> vctString;

    // 获取拖拽进来文件和文件夹
    for (UINT i = 0; i < nFileCount; i++)
    {
        ::DragQueryFile(hDropInfo, i, szFileName, sizeof(szFileName));
        dwAttribute = ::GetFileAttributes(szFileName);

        // 是否为文件夹
        if (dwAttribute & FILE_ATTRIBUTE_DIRECTORY)
        {
            ::SetCurrentDirectory(szFileName);
            EnumerateFiles(vctString);
        }
        else
        {
            vctString.push_back(szFileName);
        }
    }

    AddFiles(vctString);
    ::DragFinish(hDropInfo);
}

std::string OpenFileDialog()
{
    OPENFILENAME ofn;
    TCHAR szFile[MAX_PATH] = _T("");

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;
    ofn.lpstrFile = szFile;
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = STR_FILE_FILTER;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn))
    {
        std::string strANSI;
        return UnicodeToANSI(szFile);
    }

    return "";
}

HWND g_hwnd = NULL;
bool IsMaximize() {
    return ::IsZoomed(g_hwnd);
}

void ToggleMaximize()
{
	if (::IsZoomed(g_hwnd))
		::PostMessageW(g_hwnd, WM_SYSCOMMAND, SC_RESTORE, 0);
	else
		::PostMessageW(g_hwnd, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
}

void Minimize()
{
    ::PostMessageW(g_hwnd, WM_SYSCOMMAND, SC_MINIMIZE, 0);
}

void Close()
{
    ::PostMessageW(g_hwnd, WM_CLOSE, 0, 0);
}

void MB_CALL_TYPE onJsQuery(mbWebView webView, void* paramCPP, mbJsExecState es, int64_t queryId, int customMsgID, const utf8* request)
{
    OutputDebugStringA("onJsQuery:");
    OutputDebugStringA(request);
    OutputDebugStringA("\n");

    switch (customMsgID) {
    case 0x01:
        //system(request);
        ::ShellExecuteA(NULL, "open", request, NULL, NULL, SW_SHOW); // path  C:\\Program Files
        break;

    case 0x101:
    {
        std::string strPath = OpenFileDialog();
		if (! strPath.empty()) {
            OutputDebugStringA(strPath.c_str());
            mbResponseQuery(webView, queryId, customMsgID, strPath.c_str());
        }
        break;
    }

	case 0x102:
		std::string msg = request;
		if ("close" == msg) {
			Close();
		}
		else if ("minimize" == msg) {
			Minimize();
		}
		else if ("toggle-maximize" == msg) {
            ToggleMaximize();
		}
		else if ("is-maximized" == msg) {
			bool b = IsMaximize();
			std::string ret = b ? "true" : "false";
			mbResponseQuery(webView, queryId, customMsgID, ret.c_str());
		}
		break;
	}
}

WNDPROC g_hwndProcOld = nullptr;

LRESULT CALLBACK WndProcCustom(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message) {
    case WM_NCDESTROY:
        break;

    case WM_CLOSE:
        ::PostMessageW(g_hwnd, WM_QUIT, 0, 0);
        //PostQuitMessage(0);
        break;

    case WM_DROPFILES:
        OnDropFiles(hWnd, (HDROP)wParam);
        break;
    }

    return CallWindowProc(g_hwndProcOld, hWnd, message, wParam, lParam);
}


WNDPROC setWndProcPtr(HWND hWnd, WNDPROC wndProc)
{
    WNDPROC old = reinterpret_cast<WNDPROC>(::GetWindowLongPtr(hWnd, GWLP_WNDPROC));
    LONG_PTR result = ::SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(wndProc));
    return old;
}

std::wstring AppendExeDir(const std::wstring& strPath)
{
    TCHAR szPath[MAX_PATH];
    ::GetModuleFileName(NULL, szPath, MAX_PATH);
    ::PathRemoveFileSpec(szPath);
    ::PathAppendW(szPath, strPath.c_str());
    if (!::PathFileExists(szPath)) {
        ::MessageBoxW(NULL, szPath, L"路径不存在，请填写正确路径：", MB_OK);
        return L"";
    }

    return std::wstring(szPath);
}

mbWebView createWnd(const char* url)
{
    // WS_THICKFRAME 可调节边框，可以自己用setwindowlong修改
    // MB_WINDOW_TYPE_TRANSPARENT 透明窗体 
    // MB_WINDOW_TYPE_NO_TITLEBAR 无标题栏
    mbWebView window = mbCreateWebWindow(MB_WINDOW_TYPE_NO_TITLEBAR, NULL, 0, 0, 1200, 700);

    // mbEnableHighDPISupport(); // 57版本会crash
    // mbSetDebugConfig(window, "showDevTools", "E:\\miniblink57_local_official\\gen\\devtools\\inspector.html");
    // mbSetDebugConfig(window, "showDevTools", "..\\..\\..\\gen\\devtools\\inspector.html");
    //std::wstring strPath = AppendExeDir(L"..\\..\\..\\gen\\devtools\\inspector.html");
    //mbSetDebugConfig(window, "showDevTools", UnicodeToANSI(strPath).c_str());

    //mbSetDragEnable(window, true);
    //mbOnPaintUpdated(window, handlePaintUpdatedCallback, hWnd);

    g_hwnd = mbGetHostHWND(window);
    g_hwndProcOld = setWndProcPtr(g_hwnd, WndProcCustom);

    void* paramCPP = (void*)8;
    mbOnJsQuery(window, onJsQuery, paramCPP);

    mbLoadURL(window, url);
    mbMoveToCenter(window);
    mbShowWindow(window, TRUE);

    return window;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此处放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TUTORIALBLINKUI, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

	//::PathAppendW(szMbPath, L"..\\..\\miniblink.dll");
	//std::wstring strPath = AppendExeDir(L"..\\..\\..\\out\\Windows_Release_Win32\\miniblink.dll");

#ifdef _DEBUG
	std::wstring strPath = AppendExeDir(L"..\\..\\..\\out\\Windows_Debug_Win32\\miniblink.dll");
#else
	std::wstring strPath = AppendExeDir(L"..\\..\\..\\out\\Windows_Release_Win32\\miniblink.dll");
#endif 

	if (strPath.empty()) return 0;
	mbSetMbMainDllPath(strPath.c_str());

	mbSettings settings;
	memset(&settings, 0, sizeof(settings));
	//settings.mask = MB_ENABLE_NODEJS;
	mbInit(&settings);

	// -------- 显示mb窗口 --------
    // 加载各种网站
    //createWnd("https://www.baidu.com/");

    //createWnd("https://www.electronjs.org/zh/");
	//createWnd("https://www.electronjs.org/");
	//createWnd("https://bulma.io");
	//createWnd("https://bulma.io/documentation/overview/colors/");
	//createWnd("https://blog.csdn.net/qq316293804/article/details/14162539");

    // 这个网站crash还没解决
    //createWnd("https://getbootstrap.com/docs/5.2/components/accordion/#example");

    // 加载本地页面
	//createWnd("file:///..\\resources\\electron-quick-start\\index.html");
	//createWnd("file:///..\\resources\\electron-titlebar\\index.html");

#ifndef _DEBUG
    createWnd("https://www.runoob.com/try/try.php?filename=tryhtml_style");
	//g_windowXMP = createWnd("file:///..\\resources\\Electron-XMP-VideoPlayer\\index.html");
#endif 

    //createWnd("file:///..\\resources\\electron-all-features\\index.html");

    // -------- 显示win32窗口 --------
	// 执行应用程序初始化:
	//if (!InitInstance (hInstance, nCmdShow))
	//{
	//    return FALSE;
	//}

    // 主消息循环:
    MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

    mbUninit();
    return (int) msg.wParam;
}


//
//  函数: MyRegisterClass()
//
//  目标: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TUTORIALBLINKUI));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_TUTORIALBLINKUI);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目标: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目标: 处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 在此处添加使用 hdc 的任何绘图代码...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
