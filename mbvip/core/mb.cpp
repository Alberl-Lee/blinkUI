#define ENABLE_MB 1
#define _CRT_SECURE_NO_WARNINGS 1

#include "mbvip/core/mb.h"
#include "mbvip/core/MbWebView.h"

#include "mbvip/common/ThreadCall.h"
#include "mbvip/common/LiveIdDetect.h"
#include "mbvip/common/StringUtil.h"

#include "third_party/WebKit/Source/wtf/text/qt4/mbchar.h"

#if !defined(WIN32)
#include <gtk/gtk.h>
#endif

bool g_mbIsInit = false;
DWORD g_uiThreadId = 0;

namespace mb {
unsigned int g_mbMask = 0;
bool g_enableNativeSetCapture = true;
bool g_enableNativeSetFocus = true;
}

mbStringPtr MB_CALL_TYPE mbCreateString(const utf8* str, size_t length)
{
    return (mbStringPtr)wkeCreateString(str, length);
}

//mbStringPtr MB_CALL_TYPE mbCreateStringWithoutNullTermination(const utf8* str, size_t length)
//{
//    return (mbStringPtr)wkeCreateStringWithoutNullTermination(str, length);
//}
//
void MB_CALL_TYPE mbDeleteString(mbStringPtr str)
{
    wkeDeleteString((wkeString)str);
}

//size_t MB_CALL_TYPE mbGetStringLen(mbStringPtr str)
//{
//    return wkeGetStringLen((wkeString)str);
//}
//
//const utf8* MB_CALL_TYPE mbGetString(mbStringPtr str)
//{
//    return wkeGetString((wkeString)str);
//}

static bool checkThreadCallIsValidImpl(const char* funcName, bool isBlinkThread)
{
    base::string16 textMsg;
    if (!g_mbIsInit) {
        textMsg = u16("禁止未初始化调用此接口：");
        textMsg += common::utf8ToUtf16(funcName);
        ::MessageBoxW(nullptr, textMsg.c_str(), u16("警告"), MB_OK);
        ::TerminateProcess((HANDLE)-1, 5);
        return false;
    }

    if (isBlinkThread) {
        if (common::ThreadCall::isBlinkThread())
            return true;
    } else {
        if (common::ThreadCall::isUiThread())
            return true;
    }

#if defined(OS_WIN) 
    textMsg = u16("禁止跨线程调用此接口：");
    textMsg += common::utf8ToUtf16(funcName);
    textMsg += u16("，");

    WCHAR* temp = (WCHAR*)malloc(0x200);
    wsprintf(temp, u16("当前线程:%d，主线程：%d"), ::GetCurrentThreadId(), common::ThreadCall::getUiThreadId());
    textMsg += temp;
    free(temp);

    ::MessageBoxW(nullptr, textMsg.c_str(), u16("警告"), MB_OK);
#else
    printf("current thread:%u, main thread:%u", ::GetCurrentThreadId(), common::ThreadCall::getUiThreadId());
#endif
    ::TerminateProcess((HANDLE)-1, 5);
    return false;
}

static bool checkThreadCallIsValid(const char* funcName)
{
    return checkThreadCallIsValidImpl(funcName, false);
}

void MB_CALL_TYPE mbInit(const mbSettings* settings)
{
    if (g_mbIsInit)
        return;
    g_mbIsInit = true;

#if !defined(WIN32)
    gtk_init(nullptr, nullptr);
#endif

    //////////////////////////////////////////////////////////////////////////
    //settings = new mbSettings();
    //memset((void*)settings, 0, sizeof(settings));
    //((mbSettings*)(settings))->mask = MB_ENABLE_DISABLE_CC;
    //////////////////////////////////////////////////////////////////////////

    if (settings)
        mb::g_mbMask = settings->mask;
    
    common::ThreadCall::init((const mbSettings*)settings);
    OutputDebugStringA("mb.cpp~, mbInit\n");
}

void MB_CALL_TYPE mbUninit()
{
//     SqBind::getInst()->uninit();
//     common::ThreadCall::shutdown();
}

mbWebView MB_CALL_TYPE mbCreateWebWindow(mbWindowType type, HWND parent, int x, int y, int width, int height)
{
    checkThreadCallIsValid(__FUNCTION__);

    //licenseCheck();

    mb::MbWebView* result = new mb::MbWebView();
    result->createWkeWebWindowInUiThread(type, parent, x, y, width, height);
    common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [result] {
        result->createWkeWebWindowOrViewInBlinkThread(true);
    });

    return (int)result->getId();
}

// 原则：如果在主线程或blink线程，判断完id是否存活可以不用锁mb::MbWebView。如果是其他线程，则必须锁

void MB_CALL_TYPE mbDestroyWebView(mbWebView webviewHandle)
{
    checkThreadCallIsValid(__FUNCTION__);

    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr((int64_t)webviewHandle);
    if (!webview)
        return;

    webview->preDestroy();

    if (webview->m_destroyCallback)
        webview->m_destroyCallback(webviewHandle, webview->m_destroyCallbackParam, nullptr);

    common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [webview] {
        delete webview;
    });
}

void MB_CALL_TYPE mbMoveToCenter(mbWebView webviewHandle)
{
    checkThreadCallIsValid(__FUNCTION__);
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr((int64_t)webviewHandle);
    if (!webview)
        return;

    int width = 0;
    int height = 0;

    HWND hWnd = webview->getHostWnd();

    RECT rect = { 0 };
    ::GetWindowRect(hWnd, &rect);
    width = rect.right - rect.left;
    height = rect.bottom - rect.top;

    int parentWidth = 0;
    int parentHeight = 0;
    if (WS_CHILD == ::GetWindowLongW(hWnd, GWL_STYLE)) {
        HWND parent = ::GetParent(hWnd);
        RECT rect = { 0 };
        ::GetClientRect(parent, &rect);
        parentWidth = rect.right - rect.left;
        parentHeight = rect.bottom - rect.top;
    } else {
        parentWidth = ::GetSystemMetrics(SM_CXSCREEN);
        parentHeight = ::GetSystemMetrics(SM_CYSCREEN);
    }

    int x = (parentWidth - width) / 2;
    int y = (parentHeight - height) / 2;

    ::MoveWindow(hWnd, x, y, width, height, FALSE);
}

HWND MB_CALL_TYPE mbGetHostHWND(mbWebView webviewHandle)
{
    checkThreadCallIsValid(__FUNCTION__);
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr((int64_t)webviewHandle);
    if (!webview)
        return NULL;
    return webview->getHostWnd();
}


void MB_CALL_TYPE mbSetDebugConfig(mbWebView webviewHandle, const char* debug, const char* param)
{
    checkThreadCallIsValid(__FUNCTION__);

    if (0 == strcmp(debug, "setPrintingEdgeDistance")) {
//         std::string str(param);
//         for (int i = 0; i < 7; ++i) {
//             size_t pos = str.find(",");
//             if (std::string::npos == pos)
//                 break;
//             std::string numStr = str.substr(0, pos);
//             str = str.substr(pos + 1);
// 
//             int num = atoi(numStr.c_str());
// 
//             if (i < 4) {
//                 if (num < 0 || num > 100)
//                     continue;
//                 printing::g_edgeDistance[i] = num * 100;
//             }
//         }
        return;
    }

    if (0 == strcmp(debug, "disableNativeSetCapture")) {
        mb::g_enableNativeSetCapture = false;
    } else if (0 == strcmp(debug, "disableNativeSetFocus")) {
      mb::g_enableNativeSetFocus = false;
    }

    std::string* debugString = new std::string(debug);
    std::string* paramString = new std::string(param);

    if (*debugString == "imageEnable")
        *debugString = "imageMbEnable";
   
    common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [webviewHandle, debugString, paramString] {
        if (!webviewHandle)
            wkeSetDebugConfig(nullptr, debugString->c_str(), paramString->c_str());
        else {
            mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
            if (webview)
                wkeSetDebugConfig(webview->getWkeWebView(), debugString->c_str(), paramString->c_str());
        }        
        delete debugString;
        delete paramString;
    });
}

BOOL MB_CALL_TYPE mbFireMouseEvent(mbWebView webviewHandle, unsigned int message, int x, int y, unsigned int flags)
{
    checkThreadCallIsValid(__FUNCTION__);
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (webview)
        webview->onMouseMessage(message, x, y, flags);
   
    return true;
}

BOOL MB_CALL_TYPE mbFireContextMenuEvent(mbWebView webviewHandle, int x, int y, unsigned int flags)
{
    checkThreadCallIsValid(__FUNCTION__);
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [x, y, flags](mb::MbWebView* webview) {
        wkeFireContextMenuEvent(webview->getWkeWebView(), x, y, flags);
    });

    return true;
}

BOOL MB_CALL_TYPE mbFireMouseWheelEvent(mbWebView webviewHandle, int x, int y, int delta, unsigned int flags)
{
    checkThreadCallIsValid(__FUNCTION__);
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (!webview->getWkeWebView())
        return true;
    if (!wkeFireMouseWheelEventOnUiThread(webview->getWkeWebView(), x, y, delta, flags))
        return true;
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [x, y, delta, flags](mb::MbWebView* webview) {
        wkeFireMouseWheelEvent(webview->getWkeWebView(), x, y, delta, flags);
    });

    return true;
}

BOOL MB_CALL_TYPE mbFireKeyUpEvent(mbWebView webviewHandle, unsigned int virtualKeyCode, unsigned int flags, BOOL isSystemKey)
{
    checkThreadCallIsValid(__FUNCTION__);
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [virtualKeyCode, flags, isSystemKey](mb::MbWebView* webview) {
        wkeFireKeyUpEvent(webview->getWkeWebView(), virtualKeyCode, flags, !!isSystemKey);
    });

    return true;
}

BOOL MB_CALL_TYPE mbFireKeyDownEvent(mbWebView webviewHandle, unsigned int virtualKeyCode, unsigned int flags, BOOL isSystemKey)
{
    checkThreadCallIsValid(__FUNCTION__);
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [virtualKeyCode, flags, isSystemKey](mb::MbWebView* webview) {
        wkeFireKeyDownEvent(webview->getWkeWebView(), virtualKeyCode, flags, !!isSystemKey);

//         if (113 == virtualKeyCode) {
//             wkeSetDebugConfig(webview->getWkeWebView(), "showDevTools", "E:/mycode/miniblink49/trunk/third_party/WebKit/Source/devtools/front_end/inspector.html");
//         }

//         char* output = (char*)malloc(0x100);
//         sprintf(output, "mbFireKeyDownEvent: %d\n", virtualKeyCode);
//         OutputDebugStringA(output);
//         free(output);
    });

    return true;
}

BOOL MB_CALL_TYPE mbFireKeyPressEvent(mbWebView webviewHandle, unsigned int charCode, unsigned int flags, BOOL isSystemKey)
{
    checkThreadCallIsValid(__FUNCTION__);
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [charCode, flags, isSystemKey](mb::MbWebView* webview) {
        wkeFireKeyPressEvent(webview->getWkeWebView(), charCode, flags, !!isSystemKey);
    });

    return true;
}

BOOL MB_CALL_TYPE mbFireWindowsMessage(mbWebView webviewHandle, HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam, LRESULT* result)
{
    checkThreadCallIsValid(__FUNCTION__);

    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (!webview)
        return TRUE;

    if (WM_SETCURSOR == message) {
        if (webview->setCursorInfoTypeByCache()) {
            if (result)
                *result = 1;
            return TRUE;
        }
    } else if (WM_IME_STARTCOMPOSITION == message) {
        common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [webviewHandle, hWnd](mb::MbWebView* webview) {
            wkeRect caret = wkeGetCaretRect(webview->getWkeWebView());

            POINT offset = webview->getOffset();
            int x = caret.x + offset.x;
            int y = caret.y + offset.y;

            common::ThreadCall::callUiThreadAsync(MB_FROM_HERE, [hWnd, webviewHandle, x, y] {
                mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
                if (!webview)
                    return;

                COMPOSITIONFORM compositionForm;
                compositionForm.dwStyle = CFS_POINT | CFS_FORCE_POSITION;
                compositionForm.ptCurrentPos.x = x;
                compositionForm.ptCurrentPos.y = y;

                HIMC hIMC = ::ImmGetContext(hWnd);
                ::ImmSetCompositionWindow(hIMC, &compositionForm);
                ::ImmReleaseContext(hWnd, hIMC);
            });
        });
        return false;
    } else if (WM_IME_COMPOSITION == message) {
        if (lParam & GCS_RESULTSTR) {
            std::vector<WCHAR> buffer;
            HIMC hIMC = ::ImmGetContext(hWnd);
            buffer.resize(ImmGetCompositionStringW(hIMC, GCS_COMPSTR, NULL, 0) + 2);
            memset(&buffer[0], 0, buffer.size());
            ImmGetCompositionStringW(hIMC, GCS_COMPSTR, &buffer[0], buffer.size() - 2);
            ImmReleaseContext(hWnd, hIMC);
        }

    } else {
        common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [hWnd, message, wParam, lParam](mb::MbWebView* webview) {
            LRESULT result = 0;
            wkeFireWindowsMessage(webview->getWkeWebView(), hWnd, message, wParam, lParam, &result);
        });
    }
    return false;
}

void MB_CALL_TYPE mbSetFocus(mbWebView webviewHandle)
{
    checkThreadCallIsValid(__FUNCTION__);
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [](mb::MbWebView* webview) {
        wkeSetFocus(webview->getWkeWebView());
    });
}

void MB_CALL_TYPE mbKillFocus(mbWebView webviewHandle)
{
    checkThreadCallIsValid(__FUNCTION__);
    common::ThreadCall::callBlinkThreadAsyncWithValid(MB_FROM_HERE, webviewHandle, [](mb::MbWebView* webview) {
        wkeKillFocus(webview->getWkeWebView());
    });
}

void MB_CALL_TYPE mbShowWindow(mbWebView webviewHandle, BOOL b)
{
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (!webview)
        return;

    if (webview->getHostWnd()) {
        webview->setShow(!!b);
        return;
    }

    common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [webviewHandle, b]() {
        common::ThreadCall::callUiThreadAsync(MB_FROM_HERE, [webviewHandle, b] {
            mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
            if (!webview)
                return;
            webview->setShow(!!b);
        });
    });    
}

void MB_CALL_TYPE mbLoadURL(mbWebView webviewHandle, const utf8* url)
{
    std::string* urlString = new std::string(url);
    common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [webviewHandle, urlString] {
        mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
        if (webview)
            wkeLoadURL(webview->getWkeWebView(), urlString->c_str());
        delete urlString;
    });

    //////////////////////////////////////////////////////////////////////////
    //mbOnLoadUrlBegin(webview, handleLoadUrlBegin, nullptr);
    //////////////////////////////////////////////////////////////////////////
}


mbWebFrameHandle MB_CALL_TYPE mbWebFrameGetMainFrame(mbWebView webviewHandle)
{
    return (mbWebFrameHandle)-2;
}

class MbJsValue {
public:
    MbJsValue()
    {
        m_id = common::LiveIdDetect::get()->constructed(this);
    }

    ~MbJsValue()
    {
        common::LiveIdDetect::get()->deconstructed(m_id);
    }

    static MbJsValue* wkeJsValueSaveToMb(jsExecState es, jsValue v)
    {
        MbJsValue* mbVal = new MbJsValue();
        mbVal->m_type = kMbJsTypeV8Value;
        mbVal->m_v = v;
        return mbVal;
    }

    static MbJsValue* wkeJsValueToMb(jsExecState es, jsValue v)
    {
        MbJsValue* result = new MbJsValue();
        jsType wkeType = jsTypeOf(v);
        switch (wkeType) {
        case JSTYPE_NUMBER:
            result->m_type = kMbJsTypeNumber;
            result->m_doubleVal = jsToDouble(es, v);
            break;
        case JSTYPE_STRING:
            result->m_type = kMbJsTypeString;
            result->m_strVal = jsToString(es, v);
            break;
        case JSTYPE_BOOLEAN:
            result->m_type = kMbJsTypeBool;
            result->m_boolVal = !!jsToBoolean(es, v);
            break;
        case JSTYPE_OBJECT:
            result->m_type = kMbJsTypeString;
            result->m_strVal = "[Object]";
            break;
        case JSTYPE_FUNCTION:
            result->m_type = kMbJsTypeString;
            result->m_strVal = "[Function]";
            break;
        case JSTYPE_UNDEFINED:
            result->m_type = kMbJsTypeUndefined;
            break;
        case JSTYPE_ARRAY:
            result->m_type = kMbJsTypeString;
            result->m_strVal = "[Array]";
            break;
        case JSTYPE_NULL:
            result->m_type = kMbJsTypeNull;
            break;
        }
        return result;
    }

    int64_t getId() const { return m_id; }
    mbJsType getType() const { return m_type; }

    double getDoubleVal() const { return m_doubleVal; }
    std::string getStrVal() const { return m_strVal; }
    BOOL getBoolVal() const { return m_boolVal; }
    jsValue getJsVal() const { return m_v; }

private:
    int64_t m_id;
    mbJsType m_type;

    double m_doubleVal;
    std::string m_strVal;
    BOOL m_boolVal;

    jsValue m_v;
};

double MB_CALL_TYPE mbJsToDouble(mbJsExecState es, mbJsValue v)
{
    MbJsValue* jsV = (MbJsValue*)common::LiveIdDetect::get()->getPtrLocked(v);
    if (!jsV)
        return 0;

    double result = 0;
    if (kMbJsTypeNumber == jsV->getType())
        result = jsV->getDoubleVal();
    common::LiveIdDetect::get()->unlock(v, jsV);

    return result;
}

BOOL MB_CALL_TYPE mbJsToBoolean(mbJsExecState es, mbJsValue v)
{
    MbJsValue* jsV = (MbJsValue*)common::LiveIdDetect::get()->getPtrLocked(v);
    if (!jsV)
        return false;

    BOOL result = FALSE;
    if (kMbJsTypeBool == jsV->getType())
        result = jsV->getBoolVal();
    common::LiveIdDetect::get()->unlock(v, jsV);

    return result;
}

std::vector<std::vector<char>*>* s_sharedStringBuffers = nullptr;
static const char* createTempCharString(const char* str, size_t length)
{
    if (!str || 0 == length)
        return "";
    std::vector<char>* stringBuffer = new std::vector<char>(length);
    memcpy(&stringBuffer->at(0), str, length * sizeof(char));
    stringBuffer->push_back('\0');

    if (!s_sharedStringBuffers)
        s_sharedStringBuffers = new std::vector<std::vector<char>*>();
    s_sharedStringBuffers->push_back(stringBuffer);
    return &stringBuffer->at(0);
}

template<class T>
static void freeShareds(std::vector<T*>* s_shared)
{
    if (!s_shared)
        return;

    for (size_t i = 0; i < s_shared->size(); ++i) {
        delete s_shared->at(i);
    }
    s_shared->clear();
}

static void freeTempCharStrings()
{
    freeShareds(s_sharedStringBuffers);
}

std::vector<mbJsValue>* s_jsValues;

mbJsType MB_CALL_TYPE mbGetJsValueType(mbJsExecState es, mbJsValue v)
{
    MbJsValue* jsV = (MbJsValue*)common::LiveIdDetect::get()->getPtrLocked(v);
    if (!jsV)
        return kMbJsTypeUndefined;

    mbJsType type = jsV->getType();
    common::LiveIdDetect::get()->unlock(v, jsV);
    return type;
}

const utf8* MB_CALL_TYPE mbJsToString(mbJsExecState es, mbJsValue v)
{
    MbJsValue* jsV = (MbJsValue*)common::LiveIdDetect::get()->getPtrLocked(v);
    if (!jsV)
        return "";

    std::string result;
    if (kMbJsTypeString == jsV->getType())
        result = jsV->getStrVal();
    common::LiveIdDetect::get()->unlock(v, jsV);

    if (0 == result.size())
        return "";

    return createTempCharString(result.c_str(), result.size());
}

void MB_CALL_TYPE mbOnJsQuery(mbWebView webviewHandle, mbJsQueryCallback callback, void* param)
{
    checkThreadCallIsValid(__FUNCTION__);

    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (!webview)
        return;

    std::function<void(mbJsExecState es, int64_t queryId, int customMsg, const utf8* request)>* closure = nullptr;
    closure = new std::function<void(mbJsExecState es, int64_t queryId, int customMsg, const utf8* request)>(
        /*std::move*/(MB_FROM_HERE, [webviewHandle, callback, param](mbJsExecState es, int64_t queryId, int customMsg, const utf8* request) {
            return callback(webviewHandle, param, es, queryId, customMsg, request);
    }));
    webview->getClosure().setJsQueryClosure(closure);
}

void MB_CALL_TYPE mbResponseQuery(mbWebView webviewHandle, int64_t queryId, int customMsg, const utf8* response)
{
    std::string* requestString = new std::string(response ? response: "");
    common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [webviewHandle, queryId, customMsg, requestString] {
        std::pair<wkeWebFrameHandle, int>* idInfo = (std::pair<wkeWebFrameHandle, int>*)queryId;
        mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
        if (!webview) {
            delete idInfo;
            delete requestString;
            return;
        }

//         char queryIdString[30] = { 0 };
//         sprintf(queryIdString, "%d, %d, `", idInfo->second, customMsg);

        wkeWebView wkeWebview = webview->getWkeWebView();
//         std::string injectScript = "window.__onMbQuery__(";
//         injectScript += queryIdString;
//         injectScript += requestString->c_str();
//         injectScript += "`);";
//         wkeRunJsByFrame(wkeWebview, idInfo->first, injectScript.c_str(), false);

        jsExecState es = wkeGetGlobalExecByFrame(wkeWebview, idInfo->first);
        jsValue windowVal = jsGlobalObject(es);
        jsValue jsFunc = jsGet(es, windowVal, "__onMbQuery__");

        jsValue args[3];
        args[0] = jsInt(idInfo->second);
        args[1] = jsInt(customMsg);
        args[2] = jsString(es, requestString->c_str());
        jsCallGlobal(es, jsFunc, args, 3);       

        delete idInfo;
        delete requestString;
    });
}

mbJsValue MB_CALL_TYPE mbRunJsSync(mbWebView webviewHandle, mbWebFrameHandle frameId, const utf8* script, BOOL isInClosure)
{
    checkThreadCallIsValid(__FUNCTION__);

//     int64_t id = webview->getId();
//     std::string* scriptString = new std::string(script);
//     MbJsValue* mbVal = nullptr;
//     common::ThreadCall::callBlinkThreadSync(MB_FROM_HERE, [id, webview, frameId, scriptString, isInClosure, &mbVal] {
//         if (!common::LiveIdDetect::get()->isLive(id)) {
//             delete scriptString;
//             return;
//         }
//         wkeWebView wkeWebview = webview->getWkeWebView();
//         wkeWebFrameHandle wkeFrameId = (wkeWebFrameHandle)frameId;
//         if ((mbWebFrameHandle)-2 == frameId)
//             wkeFrameId = wkeWebFrameGetMainFrame(wkeWebview);
//         jsValue ret = wkeRunJsByFrame(wkeWebview, wkeFrameId, scriptString->c_str(), !!isInClosure);
// 
//         jsExecState es = wkeGetGlobalExecByFrame(wkeWebview, wkeFrameId);
//         mbVal = MbJsValue::wkeJsValueToMb(es, ret);
//     });
// 
//     if (!mbVal)
//         return 0;
// 
//     common::ThreadCall::callUiThreadAsync(MB_FROM_HERE, [] {
//         freeTempCharStrings();
//     });
// 
//     return mbVal->getId();

    return 0;
}

static void callRunJsCallbackOnUiThread(mbWebView webviewHandle, void* param, mbRunJsCallback callback, jsExecState es, MbJsValue* mbVal)
{
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (webview)
        callback(webviewHandle, param, es, mbVal->getId());

    freeTempCharStrings();
    delete mbVal;
}

void runJsOnBlinkThread(mbWebView webviewHandle, mbWebFrameHandle frameId, std::string* scriptString, BOOL isInClosure, mbRunJsCallback callback, void* param)
{
    mb::MbWebView* webview = (mb::MbWebView*)common::LiveIdDetect::get()->getPtr(webviewHandle);
    if (!webview) {
        delete scriptString;
        return;
    }

    wkeWebView wkeWebview = webview->getWkeWebView();
    wkeWebFrameHandle wkeFrameId = (wkeWebFrameHandle)frameId;
    if ((mbWebFrameHandle)-2 == frameId)
        wkeFrameId = wkeWebFrameGetMainFrame(wkeWebview);

    jsValue ret = wkeRunJsByFrame(wkeWebview, wkeFrameId, scriptString->c_str(), !!isInClosure);
    jsExecState es = wkeGetGlobalExecByFrame(wkeWebview, wkeFrameId);

    if (callback) {
        MbJsValue* mbVal = MbJsValue::wkeJsValueToMb(es, ret);
        common::ThreadCall::callUiThreadAsync(MB_FROM_HERE, [webviewHandle, param, callback, es, mbVal] {
            callRunJsCallbackOnUiThread(webviewHandle, param, callback, es, mbVal);
        });
    }
    delete scriptString;    
}

void MB_CALL_TYPE mbRunJs(mbWebView webviewHandle, mbWebFrameHandle frameId, const utf8* script, BOOL isInClosure, mbRunJsCallback callback, void* param, void* unuse)
{
    std::string* scriptString = new std::string(script);
    if (common::ThreadCall::isBlinkThread())
        runJsOnBlinkThread(webviewHandle, frameId, scriptString, isInClosure, callback, param);
    else {
        common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [webviewHandle, frameId, scriptString, isInClosure, callback, param] {
            runJsOnBlinkThread(webviewHandle, frameId, scriptString, isInClosure, callback, param);
        });
    }
}



void MB_CALL_TYPE mbNetSetData(mbNetJob jobPtr, void* buf, int len)
{
    if (common::ThreadCall::isBlinkThread())
        wkeNetSetData(jobPtr, buf, len);
    else {
        std::vector<char>* bufferCopy = new std::vector<char>();
        bufferCopy->resize(len);
        memcpy(&bufferCopy->at(0), buf, len);
        common::ThreadCall::callBlinkThreadAsync(MB_FROM_HERE, [jobPtr, bufferCopy] {
            wkeNetSetData(jobPtr, &bufferCopy->at(0), (int)bufferCopy->size());
            delete bufferCopy;
        });
    }    
}
