#ifndef WKE_WEB_VIEW_H
#define WKE_WEB_VIEW_H

#if (defined ENABLE_WKE) && (ENABLE_WKE == 1)
//////////////////////////////////////////////////////////////////////////

//cexer: 必须包含在后面，因为其中的 windows.h 会定义 max、min，导致 WebCore 内部的 max、min 出现错乱。
#include "wke/wkeString.h"
#include "wke/wkeUtil.h"
#include "third_party/WebKit/Source/platform/geometry/IntRect.h"
#include "third_party/WebKit/public/web/WebHistoryItem.h"
#include "third_party/WebKit/Source/wtf/OwnPtr.h"
#include "net/WebURLLoaderManager.h"
#include <map>
#include <set>

//////////////////////////////////////////////////////////////////////////

namespace content {
class WebPage;
}

namespace net {
class WebCookieJarImpl;
}

typedef void CURL;
typedef void CURLSH;

namespace wke {

struct CWebViewHandler {
    wkeTitleChangedCallback titleChangedCallback;
    void* titleChangedCallbackParam;

    wkeTitleChangedCallback mouseOverUrlChangedCallback;
    void* mouseOverUrlChangedCallbackParam;

    wkeURLChangedCallback urlChangedCallback;
    void* urlChangedCallbackParam;

    wkeURLChangedCallback2 urlChangedCallback2;
    void* urlChangedCallback2Param;

    wkePaintUpdatedCallback paintUpdatedCallback;
    void* paintUpdatedCallbackParam;

    wkePaintBitUpdatedCallback paintBitUpdatedCallback;
    void* paintBitUpdatedCallbackParam;

    wkeAlertBoxCallback alertBoxCallback;
    void* alertBoxCallbackParam;

    wkeConfirmBoxCallback confirmBoxCallback;
    void* confirmBoxCallbackParam;

    wkePromptBoxCallback promptBoxCallback;
    void* promptBoxCallbackParam;

    wkeNavigationCallback navigationCallback;
    void* navigationCallbackParam;

    wkeCreateViewCallback createViewCallback;
    void* createViewCallbackParam;

    wkeDocumentReadyCallback documentReadyCallback;
    void* documentReadyCallbackParam;

    wkeDocumentReady2Callback documentReady2Callback;
    void* documentReady2CallbackParam;

    wkeLoadingFinishCallback loadingFinishCallback;
    void* loadingFinishCallbackParam;

    wkeDownloadCallback downloadCallback;
    void* downloadCallbackParam;

    wkeDownload2Callback download2Callback;
    void* download2CallbackParam;

    wkeNetResponseCallback netResponseCallback;
    void* netResponseCallbackParam;

    wkeConsoleCallback consoleCallback;
    void* consoleCallbackParam;

    wkeCallUiThread callUiThreadCallback;
    void* callUiThreadCallbackParam;
    
    wkeLoadUrlBeginCallback loadUrlBeginCallback;
    void* loadUrlBeginCallbackParam;

    wkeLoadUrlEndCallback loadUrlEndCallback;
    void* loadUrlEndCallbackParam;

	wkeLoadUrlFailCallback loadUrlFailCallback;
	void* loadUrlFailCallbackParam;

	void* wsCallback;
	void* wsCallbackParam;

    wkeDidCreateScriptContextCallback didCreateScriptContextCallback;
    void* didCreateScriptContextCallbackParam;

    wkeWillReleaseScriptContextCallback willReleaseScriptContextCallback;
    void* willReleaseScriptContextCallbackParam;

    wkeOnOtherLoadCallback otherLoadCallback;
    void* otherLoadCallbackParam;

    wkeWindowClosingCallback windowClosingCallback;
    void* windowClosingCallbackParam;
    
    wkeWindowDestroyCallback windowDestroyCallback;
    void* windowDestroyCallbackParam;

    wkeDraggableRegionsChangedCallback draggableRegionsChangedCallback;
    void* draggableRegionsChangedCallbackParam;

    wkeStartDraggingCallback startDraggingCallback;
    void* startDraggingCallbackParam;

    wkeOnPrintCallback printCallback;
    void* printCallbackParam;

    wkeOnContextMenuItemClickCallback contextMenuItemClickCallback;
    void* contextMenuItemClickCallbackParam;

    wkeCaretChangedCallback caretChangedCallback;
    void* caretChangedCallbackParam;
    
    BOOL needDestroyWnd; // 是否在关闭时刻销毁窗口
};

class CWebView : public IWebView {
public:
    CWebView(COLORREF color);
    virtual ~CWebView();

    virtual bool create();
    virtual void destroy() ;

    static void shutdown();

    bool isValid();
    void setWillDestroy();

    const utf8* name() const ;
    const WCHAR* nameW() const;

    void setName(const utf8* name) ;
    void setName(const WCHAR* name);

	virtual bool isTransparent() const ;
	virtual void setTransparent(bool transparent) ;

	void loadURL(const utf8* inUrl);
	void loadURL(const WCHAR* url);
    
    void loadPostURL(const utf8* inUrl,const char * poastData,int nLen);
    void loadPostURL(const WCHAR * inUrl,const char * poastData,int nLen);

    void loadHTML(const utf8* html) ;
    void loadHtmlWithBaseUrl(const utf8* html, const utf8* baseUrl);
    void loadHTML(const WCHAR* html) ;

	void loadFile(const utf8* filename);
	void loadFile(const WCHAR* filename);

    const utf8* url() const ;

    void setUserAgent(const utf8 * useragent);
    void setUserAgent(const WCHAR * useragent);
    
    virtual bool isLoading() const ;
    virtual bool isLoadingSucceeded() const ;
    virtual bool isLoadingFailed() const ;
    bool isLoadingCompleted() const;
    virtual bool isDocumentReady() const ;
    virtual void stopLoading() ;
    virtual void reload() ;
    void goToOffset(int offset);
    void goToIndex(int index);

    const utf8* title() ;
    const WCHAR* titleW() ;
    
    virtual void resize(int w, int h) ;
    int width() const ;
    int height() const ;

    int contentWidth() const;
    int contentHeight() const;

	virtual int contentsWidth() const;
	virtual int contentsHeight() const;

	void setDirty(bool dirty);
	bool isDirty() const;
	void addDirtyArea(int x, int y, int w, int h);

    void layoutIfNeeded() ;
    void paint(void* bits, int pitch) ;
    void paint(void* bits, int bufWid, int bufHei, int xDst, int yDst, int w, int h, int xSrc, int ySrc, bool fKeepAlpha);
    void repaintIfNeeded();
    HDC viewDC();
    void releaseHdc();
    HWND windowHandle() const;
    void setHandle(HWND wnd);
    void setHandleOffset(int x, int y);
    void setDragDropEnable(bool b);
    void setTouchSimulateEnabled(bool b);
    void setSystemTouchEnabled(bool b);
    void setViewSettings(const wkeViewSettings*);
    //bool canGoBack() const ;
    //bool goBack() ;
    //bool canGoForward() const ;
    //bool goForward() ;
    void navigateAtIndex(int index);
    int getNavigateIndex() const;

    //void editorSelectAll() ;
    //void editorUnSelect() ;
    //void editorCopy() ;
    //void editorCut() ;
    //void editorPaste() ;
    //void editorDelete() ;
    //void editorUndo() ;
    //void editorRedo() ;

    const WCHAR* cookieW();
    const utf8* cookie();

    //void setMediaVolume(float volume) ;
    //float mediaVolume() const ;
   
	virtual bool fireMouseEvent(unsigned int message, int x, int y, unsigned int flags);
	virtual bool fireContextMenuEvent(int x, int y, unsigned int flags);
	virtual bool fireMouseWheelEvent(int x, int y, int delta, unsigned int flags);
	virtual bool fireKeyUpEvent(unsigned int virtualKeyCode, unsigned int flags, bool systemKey);
	virtual bool fireKeyDownEvent(unsigned int virtualKeyCode, unsigned int flags, bool systemKey);
	virtual bool fireKeyPressEvent(unsigned int charCode, unsigned int flags, bool systemKey);
	
    bool fireWindowsMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result);
    bool fireMouseWheelEventOnUiThread(int x, int y, int delta, unsigned int flags);

	virtual void setFocus();
	virtual void killFocus();

	virtual wkeRect getCaret();
    wkeRect caretRect();

    static int64_t wkeWebFrameHandleToFrameId(content::WebPage* page, wkeWebFrameHandle frameId);
    static wkeWebFrameHandle frameIdTowkeWebFrameHandle(content::WebPage* page, int64_t frameId);

	jsValue runJS(const WCHAR* script);
	jsValue runJS(const utf8* script);
    jsValue runJsInFrame(wkeWebFrameHandle frameId, const utf8* script, bool isInClosure);
    jsExecState globalExec() ;
    jsExecState globalExecByFrame(wkeWebFrameHandle frameId);

	void sleep();
	void wake();
	bool isAwake() const;

    //virtual void awaken() ;

    void setZoomFactor(float factor) ;
    float zoomFactor() const ;

    //void setEditable(bool editable) ;
    
    void onURLChanged(wkeURLChangedCallback callback, void* callbackParam);
    void onURLChanged2(wkeURLChangedCallback2 callback, void* callbackParam);
    void onUrlChanged(const wkeString url);
    void onTitleChanged(wkeTitleChangedCallback callback, void* callbackParam);
    void onMouseOverUrlChanged(wkeTitleChangedCallback callback, void* callbackParam);
    virtual void onPaintUpdated(wkePaintUpdatedCallback callback, void* callbackParam);
    void onPaintBitUpdated(wkePaintBitUpdatedCallback callback, void* callbackParam);
    void onCaretChanged(wkeCaretChangedCallback callback, void* callbackParam);

    void onAlertBox(wkeAlertBoxCallback callback, void* callbackParam);
    void onConfirmBox(wkeConfirmBoxCallback callback, void* callbackParam);
    void onPromptBox(wkePromptBoxCallback callback, void* callbackParam);

    void onNavigation(wkeNavigationCallback callback, void* callbackParam);
    void onCreateView(wkeCreateViewCallback callback, void* callbackParam);

    virtual void onLoadingFinish(wkeLoadingFinishCallback callback, void* callbackParam);
    virtual void onDocumentReady(wkeDocumentReadyCallback callback, void* callbackParam);
    void onDocumentReady2(wkeDocumentReady2Callback callback, void* callbackParam);
    virtual void onDownload(wkeDownloadCallback callback, void* callbackParam);
    void onDownload2(wkeDownload2Callback callback, void* callbackParam);
    
    virtual void onConsole(wkeConsoleCallback callback, void* callbackParam);
    virtual void onCallUiThread(wkeCallUiThread callback, void* callbackParam);
    void onNetResponse(wkeNetResponseCallback callback, void* callbackParam);
    
    void onLoadUrlBegin(wkeLoadUrlBeginCallback callback, void* callbackParam);
    void onLoadUrlEnd(wkeLoadUrlEndCallback callback, void* callbackParam);
	void onLoadUrlFail(wkeLoadUrlFailCallback callback, void* callbackParam);

    void onDidCreateScriptContext(wkeDidCreateScriptContextCallback callback, void* callbackParam);
    void onWillReleaseScriptContext(wkeWillReleaseScriptContextCallback callback, void* callbackParam);
    void onStartDragging(wkeStartDraggingCallback callback, void* callbackParam);
    void onPrint(wkeOnPrintCallback callback, void* param);
    void onOtherLoad(wkeOnOtherLoadCallback callback, void* callbackParam);
    void onContextMenuItemClick(wkeOnContextMenuItemClickCallback callback, void* callbackParam);
    void onDraggableRegionsChanged(wkeDraggableRegionsChangedCallback callback, void* param);

    //void setClientHandler(const wkeClientHandler* handler) ;
    //const wkeClientHandler* getClientHandler() const ;

    CWebViewHandler* getWkeHandler() const;

    content::WebPage* webPage() { return m_webPage; }

    void setUserKeyValue(const char* key, void* value);
    void* getUserKeyValue(const char* key);

    int getCursorInfoType();
    void setCursorInfoType(int type);

    void setDragFiles(const POINT* clintPos, const POINT* screenPos, wkeString files[], int filesCount);

    void setNetInterface(const char* netInterface);
    String getNetInterface() const { return m_netInterface; }

    void setProxyInfo(const String& host, unsigned long port, net::ProxyType type, const String& username, const String& password);
    String getProxy() const { return m_proxy; }
    net::ProxyType getProxyType() const { return m_proxyType; }

    void showDevTools(const utf8* url, wkeOnShowDevtoolsCallback callback, void* param);

    content::WebPage* getWebPage() const { return m_webPage; }

    CURLSH* getCurlShareHandle();
    std::string getCookieJarPath();
    void setCookieJarFullPath(const utf8* path);
    net::WebCookieJarImpl* getCookieJar();

    void setLocalStorageFullPath(const utf8* path);

    std::set<jsValue>& getPersistentJsValue() { return m_persistentJsValue; }

    int getId() const { return m_id; }

protected:
    friend class ShowDevToolsTaskObserver;

    HWND m_hWnd;
    void _initHandler();
    void _initPage(COLORREF color);
    void _initMemoryDC();

    void _loadURL(const utf8* inUrl, bool isFile);

    std::map<std::string, void*> m_userKeyValues;
    std::set<jsValue> m_persistentJsValue;

    int m_id;

    //按理这些接口应该使用CWebView来实现的，可以把它们想像成一个类，因此设置为友员符合情理。
//     friend class ToolTip;
//     friend class ChromeClient;
//     friend class ContextMenuClient;
//     friend class DrawClient;
//     friend class EditorClient;
//     friend class FrameLoaderClient;
//     friend class InspectorClient;
//     friend class PlatformStrategies;

//     OwnPtr<WebCore::Page> m_page;
//     WebCore::Frame* m_mainFrame;
    wke::CString m_url;  //记录url地址
    wke::CString m_title;
    wke::CString m_cookie;
    wke::CString m_name;
    bool m_transparent;
    bool m_isCokieEnabled;

    int m_width;
    int m_height;

    blink::IntRect m_dirtyArea;

    content::WebPage* m_webPage;

    float m_zoomFactor;

    OwnPtr<HDC> m_hdc;
    OwnPtr<HBITMAP> m_hbitmap;
    //void* m_pixels;

    bool m_awake;

    String m_netInterface;

    String m_proxy;
    net::ProxyType m_proxyType;

    friend class ShowDevToolsTaskObserver;
    bool m_isCreatedDevTools;
    wkeWebView m_devToolsWebView;

    wkeViewSettings m_settings;
};

};//namespace wke
#endif
#endif//#ifndef WKE_WEB_VIEW_H
