#if (defined ENABLE_WKE) && (ENABLE_WKE == 1)

//////////////////////////////////////////////////////////////////////////
#define BUILDING_wke 1

#include "wke/wkeString.h"
#include "wke/wkeWebView.h"
#include "wke/wkeWebWindow.h"
#include "wke/wkeGlobalVar.h"
//#include "wke/wke2.h"
#include "content/browser/WebPage.h"
#include "content/browser/PostTaskHelper.h"
#include "content/web_impl_win/BlinkPlatformImpl.h"
#include "content/web_impl_win/WebThreadImpl.h"
#include "content/web_impl_win/npapi/WebPluginImpl.h"
#include "content/web_impl_win/npapi/PluginDatabase.h"
#include "content/OrigChromeMgr.h"
#include "net/WebURLLoaderManager.h"
#include "net/ActivatingObjCheck.h"
#include "net/DefaultFullPath.h"
#include "net/CurlCacheManager.h"
#include "net/cookies/WebCookieJarCurlImpl.h"
#include "third_party/WebKit/public/web/WebKit.h"
#include "third_party/WebKit/public/web/WebFrame.h"
//#include "third_party/WebKit/public/web/WebDragOperation.h"
#include "third_party/WebKit/public/web/WebDocument.h"
#include "third_party/WebKit/public/web/WebCustomElement.h"
#include "third_party/WebKit/public/web/WebUserGestureIndicator.h"
//#include "third_party/WebKit/public/web/WebPageSerializer.h"
#include "third_party/WebKit/public/platform/WebPluginListBuilder.h"
#include "third_party/WebKit/public/platform/WebDragData.h"
#include "third_party/WebKit/Source/web/WebViewImpl.h"
#include "third_party/WebKit/Source/web/WebSettingsImpl.h"
#include "third_party/WebKit/Source/core/frame/Settings.h"
#include "third_party/WebKit/Source/core/page/Page.h"
#include "third_party/WebKit/Source/core/page/NetworkStateNotifier.h"
#include "gen/blink/platform/RuntimeEnabledFeatures.h"
#include "wtf/text/WTFString.h"
#include "wtf/text/WTFStringUtil.h"
#include "wtf/text/Base64.h"
#include "base/strings/string_util.h"
#include <v8.h>
#include "libplatform/libplatform.h"
#include "base/strings/utf_string_conversions.h"
#include "base/strings/string16.h"
#include "base/threading/thread_local.h"
#include <objbase.h>
#include <windows.h>

extern "C" BOOL __stdcall PathIsDirectoryW(LPCWSTR pszPath);

namespace blink {
char* g_navigatorPlatform;
}

namespace content {
typedef void(WINAPI* PfnUiThreadHeartbeatCallback)();
extern PfnUiThreadHeartbeatCallback g_uiThreadHeartbeatCallback;
}

namespace mc {
const SkColor s_kBgColor = 0xffffffff;
}

namespace wke {
DWORD s_threadId = 0;
base::ThreadLocalBoolean* s_reentryGuard = 0;
}

void wkeInitializeImpl(bool ocEnable)
{
    if (wke::wkeIsInit)
        return;

    wke::s_threadId = ::GetCurrentThreadId();
    wke::s_reentryGuard = new base::ThreadLocalBoolean();
    wke::s_reentryGuard->Set(false);

    CoInitializeEx(nullptr, 0);

    content::WebPage::initBlink(ocEnable);
    wke::wkeIsInit = true;
}

void WKE_CALL_TYPE wkeInitialize()
{
    wkeInitializeImpl(false);
}

void WKE_CALL_TYPE wkeInitializeEx(const wkeSettings* settings)
{
    bool ocEnable = false;
    if (settings && (settings->mask & (WKE_SETTING_EXTENSION))) {
        if (strstr(settings->extension, "EnableOc"))
            ocEnable = true;
    }
    wkeInitializeImpl(ocEnable);
    //wkeConfigure(settings);
}

BOOL WKE_CALL_TYPE wkeIsInitialize()
{
    return wke::wkeIsInit;
}

void WKE_CALL_TYPE wkeFinalize()
{
    //wkeShutdownForDebug();
}

#ifdef _DEBUG
void WKE_CALL_TYPE wkeShutdownForDebug()
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    content::BlinkPlatformImpl* platform = (content::BlinkPlatformImpl*)blink::Platform::current();
    platform->shutdown();

    CoUninitialize();

    wke::s_versionString.clear();
}
#endif

bool g_isMouseEnabled = true;


bool setDebugConfig2(wkeWebView webview, const char* debugString, const char* param)
{
	content::WebPage* webpage = nullptr;
	blink::WebViewImpl* webViewImpl = nullptr;
	blink::WebSettingsImpl* settings = nullptr;
	if (webview)
		webpage = webview->getWebPage();
	if (webpage)
		webViewImpl = webpage->webViewImpl();
	if (webViewImpl)
		settings = webViewImpl->settingsImpl();

	String stringDebug(debugString);
	Vector<String> result;
	stringDebug.split(",", result);

	if (result.size() == 0)
		return true;

	String item = result[0];
	if ("smootTextEnable" == item) {
		wke::g_smootTextEnable = atoi(param) == 1;
	}
	else if ("wsCallback" == item) {
		webview->webPage()->wkeHandler().wsCallback = (void*)(param);
		return true;
	}
	else if ("wsCallbackParam" == item) {
		webview->webPage()->wkeHandler().wsCallbackParam = (void*)(param);
		return true;
	}
	else if ("imageMbEnable" == item) {
		settings->setLoadsImagesAutomatically(atoi(param) == 1);
		settings->setImagesEnabled(atoi(param) == 1);
		return true;
	}
	else if ("jsEnable" == item) {
		settings->setJavaScriptEnabled(atoi(param) == 1);
		return true;
	}
	else if ("v8flags" == item) {
		v8::V8::SetFlagsFromString(param, strlen(param));
		return true;
	}

	return false;
}


void WKE_CALL_TYPE wkeSetDebugConfig(wkeWebView webview, const char* debugString, const char* param)
{
    if (nullptr != strstr(debugString, "paintcallbackInOtherThread")) {
        content::g_uiThreadId = (DWORD)(param);
        //blink::RuntimeEnabledFeatures::setUpdataInOtherThreadEnabled(true);
        return;
    } else if (nullptr != strstr(debugString, "setUiThreadHeartbeatCallback")) {
        content::g_uiThreadHeartbeatCallback = (content::PfnUiThreadHeartbeatCallback)(param);
        return;
    }
    
#ifndef NO_USE_ORIG_CHROME
    if (nullptr != strstr(debugString, "runUntilIdleWithoutMsgPeek")) {
        bool isReentry = wke::s_reentryGuard->Get();
        if (isReentry)
            return;

        wke::s_reentryGuard->Set(true);
        OrigChromeMgr::runUntilIdleWithoutMsgPeek();
        wke::s_reentryGuard->Set(false);
        return;
    } else if (nullptr != strstr(debugString, "runUntilIdle")) {
        BOOL isReentry = wke::s_reentryGuard->Get();
        if (isReentry)
            return;

        wke::s_reentryGuard->Set(true);
        OrigChromeMgr::runUntilIdle();
        wke::s_reentryGuard->Set(false);
        return;
    } else if (nullptr != strstr(debugString, "initOrigChromeUiThread")) {
        OrigChromeMgr::getInst()->initUiThread();
        return;
    } else if (nullptr != strstr(debugString, "initOrigChromeBlinkThread")) {
        //blink::RuntimeEnabledFeatures::setCompositorAnimationTimelinesEnabled(true);
        blink::RuntimeEnabledFeatures::setCompositorWorkerEnabled(true);
//         blink::RuntimeEnabledFeatures::setSlimmingPaintEnabled(true);
//         blink::RuntimeEnabledFeatures::setSlimmingPaintCompositorLayerizationEnabled(false);
//         blink::RuntimeEnabledFeatures::setSlimmingPaintUnderInvalidationCheckingEnabled(false);
        blink::RuntimeEnabledFeatures::setSlimmingPaintStrictCullRectClippingEnabled(false);

        GLImplType type = kGLImplTypeNone;
        if (nullptr != strstr(debugString, "egles2")) {
            type = kGLImplTypeEGLGLES2;
        } else if (nullptr != strstr(debugString, "swiftshader")) {
            type = kGLImplTypeEgles2Swiftshader;
        }

        OrigChromeMgr::getInst()->setGLImplType(type);
        OrigChromeMgr::getInst()->initBlinkThread();
        return;
    } else if (nullptr != strstr(debugString, "postBlinkTask")) {
        OrigChromeMgr::postBlinkTask((OrigTaskType)param);
        return;
    } else if (nullptr != strstr(debugString, "postUiTask")) {
        OrigChromeMgr::postUiTask((OrigTaskType)param);
        return;
    }
#endif
    else if (nullptr != strstr(debugString, "disableNativeSetCapture")) {
        wke::g_enableNativeSetCapture = false;
        return;
    } else if (nullptr != strstr(debugString, "setPluginListCallback")) {
        wke::g_getPluginListCallback = (wkeGetPluginListCallback)param;
        return;
    } else if (nullptr != strstr(debugString, "enableNodejs")) {
#if ENABLE_NODEJS
        OutputDebugStringA("enableNodejs!!\n");
        enableNodejs();
#endif
    }

    wke::checkThreadCallIsValid(__FUNCTION__);

    //if (wke::setDebugConfig(webview, debugString, param))
    //    return;
	if (setDebugConfig2(webview, debugString, param))
		return;


    content::WebPage* webpage = nullptr;
    blink::WebViewImpl* webViewImpl = nullptr;
    blink::WebSettingsImpl* settings = nullptr;
    if (webview)
        webpage = webview->getWebPage();
    if (webpage)
        webViewImpl = webpage->webViewImpl();
    if (webViewImpl)
        settings = webViewImpl->settingsImpl();

    String stringDebug(debugString);
    Vector<String> result;
    stringDebug.split(",", result);
    for (size_t i = 0; i < result.size(); ++i) {
        String item = result[i];
        if ("alwaysIsNotSolideColor" == item) {
            //blink::RuntimeEnabledFeatures::setAlwaysIsNotSolideColorEnabled(true);
        } else if ("drawDirtyDebugLine" == item) {
            //blink::RuntimeEnabledFeatures::setDrawDirtyDebugLineEnabled(true);
        } else if ("drawTileLine" == item) {
            wke::g_drawTileLineEnable = true;
            //blink::RuntimeEnabledFeatures::setDrawTileLineEnabled(true);
        } else if ("flashChineseEnable" == item) {
            wke::g_flashChineseEnable = true;
        } else if ("cutOutsNpapiRects" == item) {
            wke::g_cutOutsNpapiRectsEnable = true;
        } else if ("decodeUrlRequest" == item) {
            wke::g_isDecodeUrlRequest = true;
        } else if ("showDevTools" == item) {
            webview->showDevTools(param, nullptr, nullptr);
        } else if ("wakeMinInterval" == item) {
            wke::g_kWakeMinInterval = atoi(param);
        } else if ("drawMinInterval" == item) {
            int drawMinInterval = atoi(param);
            drawMinInterval = drawMinInterval / 1000.0;
            webpage->setDrawMinInterval(drawMinInterval);
        } else if ("minimumFontSize" == item) {
            if (settings)
                settings->setMinimumFontSize(atoi(param));
        } else if ("minimumLogicalFontSize" == item) {
            if (settings)
                settings->setMinimumLogicalFontSize(atoi(param));
        } else if ("defaultFontSize" == item) {
            if (settings)
                settings->setDefaultFontSize(atoi(param));
        } else if ("defaultFixedFontSize" == item) {
            if (settings)
                settings->setDefaultFixedFontSize(atoi(param));
        } else if ("tipPaintCallback" == item) {
            wke::g_tipPaintCallback = (void*)param;
        } else if ("contentScale" == item) {
            wke::g_contentScale = atoi(param) / 100.0;
        } else if ("antiAlias" == item) {
            wke::g_rendererAntiAlias = atoi(param) == 1;
        } else if ("saveDiskCache" == item) {
            net::CurlCacheManager::getInstance()->save();
        } else if ("diskCache" == item) {
            wke::g_diskCacheEnable = atoi(param) == 1;
            if (net::CurlCacheManager::getInstance()->cacheDirectory().isEmpty()) {
                //使用默认缓存目录
                std::string path = net::getDefaultLocalStorageFullPath();
                path += ("cache");
                net::CurlCacheManager::getInstance()->setCacheDirectory(String::fromUTF8(path.c_str()));
            }
        } else if ("diskCachePath" == item) {
            if (param) {
                wke::g_diskCacheEnable = 1;
                net::CurlCacheManager::getInstance()->setCacheDirectory(param);
            }
        } else if ("diskCacheLevel" == item) {
            if (param)
                net::CurlCacheManager::getInstance()->setCacheLevel(atoi(param));
        } else if ("diskCacheLimit" == item) {
            if (param)
                net::CurlCacheManager::getInstance()->setStorageSizeLimit(atoi(param));
        } else if ("diskCacheLimitDisk" == item) {
            if (param)
                net::CurlCacheManager::getInstance()->setStorageSizeLimitDisk(atoi(param));
        } else if ("consoleOutput" == item) {
            wke::g_consoleOutputEnable = atoi(param) == 1;
        } else if ("setStackLimit" == item) {
            uintptr_t currentStackPosition = reinterpret_cast<uintptr_t>(&currentStackPosition);
            v8::Isolate::GetCurrent()->SetStackLimit(currentStackPosition - (uintptr_t)atoi(param));
        } else if ("disableNavigatorPlugins" == item) {
            wke::g_navigatorPluginsEnable = false;
        } else if ("setDNS" == item) {
            wke::g_DNS = WTF::adoptPtr(new std::string(param));
        } else if ("setGeolocationPosition" == item) {
            if (!param)
                wke::g_geoPos.clear();
            else
                wke::g_geoPos = WTF::adoptPtr(new wkeGeolocationPosition(*(wkeGeolocationPosition*)(param)));
        } else if ("inspectElementAt" == item) {
            POINT screenPt = { 0 };
            ::GetCursorPos(&screenPt);

            POINT clientPt = screenPt;
            ::ScreenToClient(webpage->getHWND(), &clientPt);
            webpage->inspectElementAt(clientPt.x, clientPt.y);
        } else if ("releaseHdc" == item) {
            webpage->releaseHdc();
        } else if ("backKeydownEnable" == item) {
            wke::g_backKeydownEnable = atoi(param) == 1;
        } else if ("jsClickEnable" == item) {
            wke::g_jsClickEnable = atoi(param) == 1;
        }
    }
}


void WKE_CALL_TYPE wkeSetHandle(wkeWebView webView, HWND wnd)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->setHandle(wnd);
}
void WKE_CALL_TYPE wkeSetTransparent(wkeWebView webView, bool transparent)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->setTransparent(transparent);
}

void WKE_CALL_TYPE wkeShowDevtools(wkeWebView webView, const WCHAR* path, wkeOnShowDevtoolsCallback callback, void* param)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    std::vector<char> pathUtf8;
    base::string16 path16(path);

    WTF::WCharToMByte(path16.c_str(), path16.size(), &pathUtf8, CP_UTF8);
    pathUtf8.push_back('\0');
    webView->showDevTools(&pathUtf8[0], callback, param);
}

void WKE_CALL_TYPE wkeLoadURL(wkeWebView webView, const utf8* url)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->loadURL(url);
}

void WKE_CALL_TYPE wkeLoadURLW(wkeWebView webView, const WCHAR* url)
{
	WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
	webView->loadURL(url);
}

void WKE_CALL_TYPE wkeResize(wkeWebView webView, int w, int h)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->resize(w, h);
}

void WKE_CALL_TYPE wkeAddDirtyArea(wkeWebView webView, int x, int y, int w, int h)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->addDirtyArea(x, y, w, h);
}
void WKE_CALL_TYPE wkeRepaintIfNeeded(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    if (webView)
        webView->repaintIfNeeded();
}

HDC WKE_CALL_TYPE wkeGetViewDC(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, nullptr);
    return webView->viewDC();
}

void WKE_CALL_TYPE wkeUnlockViewDC(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    return webView->releaseHdc();
}

HWND WKE_CALL_TYPE wkeGetHostHWND(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, nullptr);
    return webView->windowHandle();
}


BOOL WKE_CALL_TYPE wkeFireMouseEvent(wkeWebView webView, unsigned int message, int x, int y, unsigned int flags)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, false);
    return webView->fireMouseEvent(message, x, y, flags);
}

BOOL WKE_CALL_TYPE wkeFireContextMenuEvent(wkeWebView webView, int x, int y, unsigned int flags)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, false);
    return webView->fireContextMenuEvent(x, y, flags);
}

BOOL WKE_CALL_TYPE wkeFireMouseWheelEvent(wkeWebView webView, int x, int y, int delta, unsigned int flags)
{
    return webView->fireMouseWheelEvent(x, y, delta, flags);
}

BOOL WKE_CALL_TYPE wkeFireMouseWheelEventOnUiThread(wkeWebView webView, int x, int y, int delta, unsigned int flags)
{
    return webView->fireMouseWheelEventOnUiThread(x, y, delta, flags);
}

BOOL WKE_CALL_TYPE wkeFireKeyUpEvent(wkeWebView webView, unsigned int virtualKeyCode, unsigned int flags, bool systemKey)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, false);
    return webView->fireKeyUpEvent(virtualKeyCode, flags, systemKey);
}

BOOL WKE_CALL_TYPE wkeFireKeyDownEvent(wkeWebView webView, unsigned int virtualKeyCode, unsigned int flags, bool systemKey)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, false);
    return webView->fireKeyDownEvent(virtualKeyCode, flags, systemKey);
}

BOOL WKE_CALL_TYPE wkeFireKeyPressEvent(wkeWebView webView, unsigned int charCode, unsigned int flags, bool systemKey)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, false);
    return webView->fireKeyPressEvent(charCode, flags, systemKey);
}

BOOL WKE_CALL_TYPE wkeFireWindowsMessage(wkeWebView webView, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, false);
    return webView->fireWindowsMessage(hWnd, message, wParam, lParam, result);
}

void WKE_CALL_TYPE wkeSetFocus(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    if (!webView)
        return;
    webView->setFocus();

    if (webView->windowHandle())
        ::SetFocus(webView->windowHandle());
}

void WKE_CALL_TYPE wkeKillFocus(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    if (!webView)
        return;
    webView->killFocus();
}

wkeRect WKE_CALL_TYPE wkeGetCaretRect(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, wkeRect());
    return webView->caretRect();
}

jsExecState WKE_CALL_TYPE wkeGetGlobalExecByFrame(wkeWebView webView, wkeWebFrameHandle frameId)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, nullptr);
    return webView->globalExecByFrame(frameId);
}

void WKE_CALL_TYPE wkeWake(wkeWebView webView)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    if (webView)
        webView->wake();

    static double s_time = 0;
    double t = WTF::currentTimeMS();
    double det = t - s_time;
    if (det < wke::g_kWakeMinInterval)
        return;
    s_time = t;

    content::WebThreadImpl* threadImpl = (content::WebThreadImpl*)(blink::Platform::current()->currentThread());
    threadImpl->fire();
}

void WKE_CALL_TYPE wkeSetZoomFactor(wkeWebView webView, float factor)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    if (!webView) {
        content::BlinkPlatformImpl* platform = (content::BlinkPlatformImpl*)blink::Platform::current();
        platform->setZoom(factor);
        return;
    }

    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->setZoomFactor(factor);
}

float WKE_CALL_TYPE wkeGetZoomFactor(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, 0);
    return webView->zoomFactor();
}

void WKE_CALL_TYPE wkeOnCaretChanged(wkeWebView webView, wkeCaretChangedCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onCaretChanged(callback, callbackParam);
}

void WKE_CALL_TYPE wkeOnPaintUpdated(wkeWebView webView, wkePaintUpdatedCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onPaintUpdated(callback, callbackParam);
}

void WKE_CALL_TYPE wkeOnPaintBitUpdated(wkeWebView webView, wkePaintBitUpdatedCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onPaintBitUpdated(callback, callbackParam);
}

void WKE_CALL_TYPE wkeOnAlertBox(wkeWebView webView, wkeAlertBoxCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onAlertBox(callback, callbackParam);
}

void WKE_CALL_TYPE wkeOnConfirmBox(wkeWebView webView, wkeConfirmBoxCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onConfirmBox(callback, callbackParam);
}

void WKE_CALL_TYPE wkeOnPromptBox(wkeWebView webView, wkePromptBoxCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onPromptBox(callback, callbackParam);
}

void WKE_CALL_TYPE wkeOnCreateView(wkeWebView webView, wkeCreateViewCallback callback, void* param)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onCreateView(callback, param);
}

void WKE_CALL_TYPE wkeOnDocumentReady2(wkeWebView webView, wkeDocumentReady2Callback callback, void* param)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onDocumentReady2(callback, param);
}

void WKE_CALL_TYPE wkeUtilSetUiCallback(wkeUiThreadPostTaskCallback callback) 
{
    wke::g_wkeUiThreadPostTaskCallback = callback;
}

void WKE_CALL_TYPE wkeSetUIThreadCallback(wkeWebView webView, wkeCallUiThread callback, void* param)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onCallUiThread(callback, param);
}

void WKE_CALL_TYPE wkeOnDidCreateScriptContext(wkeWebView webView, wkeDidCreateScriptContextCallback callback, void* callbackParam)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->onDidCreateScriptContext(callback, callbackParam);
}


wkeTempCallbackInfo* WKE_CALL_TYPE wkeGetTempCallbackInfo(wkeWebView webView)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    return &wke::g_wkeTempCallbackInfo;
}

void WKE_CALL_TYPE wkeDeleteWillSendRequestInfo(wkeWebView webWindow, wkeWillSendRequestInfo* info)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    wkeDeleteString(info->url);
    if (info->newUrl)
        wkeDeleteString(info->newUrl);
    wkeDeleteString(info->method);
    wkeDeleteString(info->referrer);
    delete info;
}


wkeWebFrameHandle WKE_CALL_TYPE wkeWebFrameGetMainFrame(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, nullptr);
    content::WebPage* page = webView->webPage();
    if (!page)
        return nullptr;
    blink::WebFrame* frame = page->mainFrame();
    if (!frame)
        return nullptr;
    return wke::CWebView::frameIdTowkeWebFrameHandle(page, page->getFrameIdByBlinkFrame(frame));
}

jsValue WKE_CALL_TYPE wkeRunJsByFrame(wkeWebView webView, wkeWebFrameHandle frameId, const utf8* script, bool isInClosure)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, jsUndefined());
    return webView->runJsInFrame(frameId, script, isInClosure);
}


const utf8* WKE_CALL_TYPE wkeGetString(const wkeString s)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    return s ? s->string() : "";
}

const WCHAR* WKE_CALL_TYPE wkeGetStringW(const wkeString string)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    return string ? string->stringW() : u16("");
}

void WKE_CALL_TYPE wkeSetString(wkeString string, const utf8* str, size_t len)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    if (!string)
        return;

    if (nullptr == str) {
        str = "";
        len = 0;
    } else {
        if (len == 0)
            len = strlen(str);
    }

    string->setString(str, len, true);
}
wkeString WKE_CALL_TYPE wkeCreateString(const utf8* str, size_t len)
{
    wkeString wkeStr = new wke::CString(str, len, true);
    return wkeStr;
}

void WKE_CALL_TYPE WKE_CALL_TYPE wkeDeleteString(wkeString str)
{
    delete str;
}


int WKE_CALL_TYPE wkeGetCursorInfoType(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, 0);
    return webView->getCursorInfoType();
}

void WKE_CALL_TYPE wkeSetCursorInfoType(wkeWebView webView, int type)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);
    webView->setCursorInfoType(type);
}

wkeWebView WKE_CALL_TYPE wkeCreateWebWindow(wkeWindowType type, HWND parent, int x, int y, int width, int height)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    wke::CWebWindow* webWindow = new wke::CWebWindow(mc::s_kBgColor);
    if (!webWindow->createWindow(parent, type, x, y, width, height)) {
        delete webWindow;
        return NULL;
    }

    return webWindow;
}

wkeWebView WKE_CALL_TYPE wkeCreateWebCustomWindow(const wkeWindowCreateInfo* info)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    wke::CWebWindow* webWindow = new wke::CWebWindow(info->color);
    if (!webWindow->createWindow(info)) {
        delete webWindow;
        return NULL;
    }

    return webWindow;
}

wkeWebView WKE_CALL_TYPE wkeCreateWebView()
{
    wke::CWebView* webView = new wke::CWebView(mc::s_kBgColor);
    webView->webPage()->setNeedAutoDrawToHwnd(false);

    return webView;
}

static void destroyWebViewAsyn(wkeWebView webView)
{
    if (!webView)
        return;

    std::set<wkeWebView>::iterator pos = wke::g_liveWebViews.find(webView);
    if (pos != wke::g_liveWebViews.end())
        delete webView;
}

void destroyWebView(wkeWebView webView, bool needDestryWin)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, (void)0);

    if (webView->getWkeHandler()->windowDestroyCallback)
        webView->getWkeHandler()->windowDestroyCallback(webView, webView->getWkeHandler()->windowDestroyCallbackParam);

    webView->setWillDestroy();
    HWND hWnd = wkeGetHostHWND(webView);

    content::postTaskToMainThread(FROM_HERE, [webView] {
        destroyWebViewAsyn(webView);
    });
    if (needDestryWin) // 为了兼容别人的老程序，这里全都关闭窗口算了
        ::PostMessageW(hWnd, WM_CLOSE, 0, 0);
}

void WKE_CALL_TYPE wkeDestroyWebView(wkeWebView webView)
{
    destroyWebView(webView, false);
}

void WKE_CALL_TYPE wkeDestroyWebWindow(wkeWebView webWindow)
{
    destroyWebView(webWindow, true);
}


void WKE_CALL_TYPE wkeOnWindowDestroy(wkeWebView webWindow, wkeWindowDestroyCallback callback, void* param)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webWindow, (void)0);
    if (wke::CWebWindow* window = static_cast<wke::CWebWindow*>(webWindow))
        return window->onDestroy(callback, param);
}

void WKE_CALL_TYPE wkeOnDraggableRegionsChanged(wkeWebView webWindow, wkeDraggableRegionsChangedCallback callback, void* param)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webWindow, (void)0);
    if (wke::CWebView* window = static_cast<wke::CWebView*>(webWindow))
        return window->onDraggableRegionsChanged(callback, param);
}

void WKE_CALL_TYPE wkeShowWindow(wkeWebView webWindow, bool showFlag)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webWindow, (void)0);
    if (wke::CWebWindow* window = static_cast<wke::CWebWindow*>(webWindow))
        return window->show(showFlag);
}
void WKE_CALL_TYPE wkeSetWindowTitle(wkeWebView webWindow, const utf8* title)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webWindow, (void)0);
    if (wke::CWebWindow* window = static_cast<wke::CWebWindow*>(webWindow))
        return window->setTitle(title);
}

static String memBufToString(wkeMemBuf* stringType)
{
    if (!stringType || !stringType->length)
        return String();
    return blink::WebString::fromUTF8((const char*)stringType->data, stringType->length);
}

void WKE_CALL_TYPE wkeSetDeviceParameter(wkeWebView webView, const char* device, const char* paramStr, int paramInt, float paramFloat)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    if (0 == strcmp(device, "navigator.maxTouchPoints")) {
        blink::WebSettingsImpl* settings = webView->webPage()->webViewImpl()->settingsImpl();
        if (settings)
            settings->setMaxTouchPoints(paramInt);
    } else if (0 == strcmp(device, "navigator.platform")) {
        if (blink::g_navigatorPlatform)
            free(blink::g_navigatorPlatform);
        int length = strlen(paramStr);
        blink::g_navigatorPlatform = (char*)malloc(length + 1);
        memset(blink::g_navigatorPlatform, 0, length + 1);
        strncpy(blink::g_navigatorPlatform, paramStr, length);
    } else if (0 == strcmp(device, "navigator.hardwareConcurrency")) {
        content::BlinkPlatformImpl* platform = (content::BlinkPlatformImpl*)blink::Platform::current();
        platform->setNumberOfProcessors(paramInt);
    } else if (0 == strcmp(device, "outerWidth")) {
        wke::g_outerWidth = paramInt;
    } else if (0 == strcmp(device, "outerHeight")) {
        wke::g_outerHeight = paramInt;        
    } else if (0 == strcmp(device, "screen.width")) {
        blink::WebScreenInfo info = webView->webPage()->screenInfo();
        info.rect.width = paramInt;
        webView->webPage()->setScreenInfo(info);
    } else if (0 == strcmp(device, "screen.height")) {
        blink::WebScreenInfo info = webView->webPage()->screenInfo();
        info.rect.height = paramInt;
        webView->webPage()->setScreenInfo(info);
    } else if (0 == strcmp(device, "screen.availWidth")) {
        blink::WebScreenInfo info = webView->webPage()->screenInfo();
        info.availableRect.width = paramInt;
        webView->webPage()->setScreenInfo(info);
    } else if (0 == strcmp(device, "screen.availHeight")) {
        blink::WebScreenInfo info = webView->webPage()->screenInfo();
        info.availableRect.height = paramInt;
        webView->webPage()->setScreenInfo(info);
    } else if (0 == strcmp(device, "screen.pixelDepth") || 0 == strcmp(device, "screen.pixelDepth")) {
        blink::WebScreenInfo info = webView->webPage()->screenInfo();
        info.depth = paramInt;
        webView->webPage()->setScreenInfo(info);
    } else if (0 == strcmp(device, "navigator.vendor")) {        
        //webView->webPage()->webViewImpl()->page()->settings().setVendor(paramStr);
    } else if (0 == strcmp(device, "navigator.javaEnabled")) {
        //webView->webPage()->webViewImpl()->page()->settings().setJavaEnabled(paramInt);
    } else if (0 == strcmp(device, "window.devicePixelRatio")) {
        wkeSetZoomFactor(webView, paramFloat);
    } else if (0 == strcmp(device, "navigator.deviceMemory")) {
        wke::g_navigatorDeviceMemory = paramInt;
    } else if (0 == strcmp(device, "navigator.connection.type")) {
        //blink::networkStateNotifier().setWebConnectionType((blink::WebConnectionType)paramInt);
    } else if (0 == strcmp(device, "navigator.connection.downlink")) {
        //blink::networkStateNotifier().setDownlink(paramInt);
    } else if (0 == strcmp(device, "navigator.connection.effectiveType")) {
        //blink::networkStateNotifier().setEffectiveType(paramStr);
    } else if (0 == strcmp(device, "navigator.connection.rtt")) {
        //blink::networkStateNotifier().setRtt(paramInt);
    } else if (0 == strcmp(device, "navigator.connection.saveData")) {
        //blink::networkStateNotifier().setSaveData(paramInt == 0);
    } else if (0 == strcmp(device, "navigator.appCodeName")) {
        wke::g_navigatorAppCodeName = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.appName")) {
        wke::g_navigatorAppName = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.appVersion")) {
        wke::g_navigatorAppVersion = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.product")) {
        wke::g_navigatorProduct = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.productSub")) {
        wke::g_navigatorProductSub = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.vendorSub")) {
        wke::g_navigatorVendorSub = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.language")) {
        wke::g_navigatorLanguage = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.oscpu")) {
        wke::g_navigatorOscpu = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.buildID")) {
        wke::g_navigatorBuildID = WTF::adoptPtr(new std::string(paramStr));
    } else if (0 == strcmp(device, "navigator.languages")) {
        if (!paramStr)
            wke::g_navigatorLanguages.clear();
        else {
            wke::g_navigatorLanguages = WTF::adoptPtr(new WTF::Vector<String>());
            String temp(paramStr);
            temp.split('|', *wke::g_navigatorLanguages);
        }
    } else if (0 == strcmp(device, "navigator.hardwareConcurrency")) {
        wke::g_navigatorHardwareConcurrency = paramInt;
    } else if (0 == strcmp(device, "navigator.maxTouchPoints")) {
        wke::g_navigatorMaxTouchPoints = paramInt;
    }
}

void WKE_CALL_TYPE wkeAddNpapiPlugin(wkeWebView webView, void* initializeFunc, void* getEntryPointsFunc, void* shutdownFunc)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
#if defined(OS_WIN)
    RefPtr<content::PluginPackage> package = content::PluginPackage::createVirtualPackage(
        (NP_InitializeFuncPtr)initializeFunc,
        (NP_GetEntryPointsFuncPtr) getEntryPointsFunc,
        (NPP_ShutdownProcPtr) shutdownFunc
        );

//     content::PluginDatabase* database = content::PluginDatabase::installedPlugins();
//     database->addVirtualPlugin(package);
//     database->setPreferredPluginForMIMEType(mime, package.get());
#endif
}

void WKE_CALL_TYPE wkeSetMediaPlayerFactory(wkeWebView webView, wkeMediaPlayerFactory factory, wkeOnIsMediaPlayerSupportsMIMEType callback)
{
    wke::g_wkeMediaPlayerFactory = factory;
    wke::g_onIsMediaPlayerSupportsMIMETypeCallback = callback;
}

int WKE_CALL_TYPE wkeGetWebviewId(wkeWebView webView)
{
    WKE_CHECK_WEBVIEW_AND_THREAD_IS_VALID(webView, 0);
    return webView->getId();
}

BOOL WKE_CALL_TYPE wkeIsWebviewAlive(int id)
{
    return net::ActivatingObjCheck::inst()->isActivating(id);
}

BOOL WKE_CALL_TYPE wkeIsWebviewValid(wkeWebView webView)
{
    return wke::checkWebViewIsValid(webView);
}


void WKE_CALL_TYPE wkeGC(wkeWebView webView, long intervalSec)
{
    wke::checkThreadCallIsValid(__FUNCTION__);
    content::BlinkPlatformImpl* platformImpl = (content::BlinkPlatformImpl*)blink::Platform::current();
    platformImpl->setGcTimer((double)intervalSec);
}

namespace wke {

bool checkThreadCallIsValid(const char* funcName)
{
    String output;
    if (!wke::wkeIsInit) {
#if defined(OS_WIN)
        output = u16("禁止初始化前调用此接口：");
        output.append(funcName);
        ::MessageBoxW(nullptr, output.charactersWithNullTermination().data(), u16("警告！"), MB_OK);
        ::TerminateProcess((HANDLE)-1, 5);
#else
        printf("don't call this call before init\n");
        abort();
#endif
        return false;
    }

    if (WTF::isMainThread())
        return true;
#if defined(OS_WIN)
    output = u16("禁止多线程调用此接口：");
    output.append(funcName);
    output.append(u16("。当前线程id："));
    output.append(String::number(::GetCurrentThreadId()));
    output.append(u16("，主线程id："));
    output.append(String::number(s_threadId));
    
    ::MessageBoxW(nullptr, output.charactersWithNullTermination().data(), u16("警告！"), MB_OK);
    ::TerminateProcess((HANDLE)-1, 5);
#else
    printf("don't call this call cross thread, this thread:%d, main thread:%d\n", ::GetCurrentThreadId(), s_threadId);
    abort();
#endif
    return false;
}

bool checkWebViewIsValid(wkeWebView webView)
{
    if (g_liveWebViews.find(webView) == g_liveWebViews.end())
        return false;
    return webView->isValid();
}

}

#endif