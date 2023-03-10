// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8Headers.h"

#include "bindings/core/v8/Dictionary.h"
#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8Iterator.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/modules/v8/V8Headers.h"
#include "core/dom/Document.h"
#include "core/frame/LocalDOMWindow.h"
#include "core/frame/UseCounter.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8Headers::wrapperTypeInfo = { gin::kEmbedderBlink, V8Headers::domTemplate, V8Headers::trace, V8Headers::traceWrappers, 0, nullptr, "Headers", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in Headers.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& Headers::s_wrapperTypeInfo = V8Headers::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, Headers>::value,
    "Headers inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&Headers::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "Headers is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace HeadersV8Internal {

    static void appendMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "append");

        Headers* impl = V8Headers::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 2)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(2, info.Length()));
            return;
        }

        V8StringResource<> name;
        V8StringResource<> value;
        name = toByteString(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        value = toByteString(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.hadException())
            return;

        impl->append(name, value, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
    }

    MODULES_EXPORT void appendMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::appendMethod(info);
    }

    static void deleteMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "delete");

        Headers* impl = V8Headers::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> key;
        key = toByteString(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        impl->remove(key, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
    }

    MODULES_EXPORT void deleteMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::deleteMethod(info);
    }

    static void getMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "get");

        Headers* impl = V8Headers::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> key;
        key = toByteString(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        String result = impl->get(key, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValueStringOrNull(info, result, info.GetIsolate());
    }

    MODULES_EXPORT void getMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::getMethod(info);
    }

    static void getAllMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "getAll");

        Headers* impl = V8Headers::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> name;
        name = toByteString(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        Vector<String> result = impl->getAll(name, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, ToV8(result, info.Holder(), info.GetIsolate()));
    }

    MODULES_EXPORT void getAllMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        UseCounter::count(currentExecutionContext(info.GetIsolate()), UseCounter::V8Headers_GetAll_Method);
        HeadersV8Internal::getAllMethod(info);
    }

    static void hasMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "has");

        Headers* impl = V8Headers::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> key;
        key = toByteString(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        bool result = impl->has(key, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValueBool(info, result);
    }

    MODULES_EXPORT void hasMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::hasMethod(info);
    }

    static void setMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "set");

        Headers* impl = V8Headers::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 2)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(2, info.Length()));
            return;
        }

        V8StringResource<> key;
        V8StringResource<> value;
        key = toByteString(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        value = toByteString(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.hadException())
            return;

        impl->set(key, value, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
    }

    MODULES_EXPORT void setMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::setMethod(info);
    }

    static void keysMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "keys");

        Headers* impl = V8Headers::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->keysForBinding(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void keysMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::keysMethod(info);
    }

    static void valuesMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "values");

        Headers* impl = V8Headers::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->valuesForBinding(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void valuesMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::valuesMethod(info);
    }

    static void entriesMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "entries");

        Headers* impl = V8Headers::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->entriesForBinding(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void entriesMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::entriesMethod(info);
    }

    static void forEachMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "forEach");

        Headers* impl = V8Headers::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        ScriptValue callback;
        ScriptValue thisArg;
        if (!(info[0]->IsObject() && v8::Local<v8::Object>::Cast(info[0])->IsCallable())) {
            exceptionState.throwTypeError("The callback provided as parameter 1 is not a function.");

            return;
        }
        callback = ScriptValue(ScriptState::current(info.GetIsolate()), info[0]);

        thisArg = ScriptValue(ScriptState::current(info.GetIsolate()), info[1]);

        impl->forEachForBinding(scriptState, ScriptValue(scriptState, info.Holder()), callback, thisArg, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
    }

    MODULES_EXPORT void forEachMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::forEachMethod(info);
    }

    static void iteratorMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "Headers", "iterator");

        Headers* impl = V8Headers::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->iterator(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void iteratorMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HeadersV8Internal::iteratorMethod(info);
    }

    static void constructor1(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ConstructionContext, "Headers");

        Headers* impl = Headers::create(exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8::Local<v8::Object> wrapper = info.Holder();
        wrapper = impl->associateWithWrapper(info.GetIsolate(), &V8Headers::wrapperTypeInfo, wrapper);
        v8SetReturnValue(info, wrapper);
    }

    static void constructor2(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ConstructionContext, "Headers");

        Headers* input;
        input = V8Headers::toImplWithTypeCheck(info.GetIsolate(), info[0]);
        if (!input) {
            exceptionState.throwTypeError("parameter 1 is not of type 'Headers'.");

            return;
        }

        Headers* impl = Headers::create(input, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8::Local<v8::Object> wrapper = info.Holder();
        wrapper = impl->associateWithWrapper(info.GetIsolate(), &V8Headers::wrapperTypeInfo, wrapper);
        v8SetReturnValue(info, wrapper);
    }

    static void constructor3(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ConstructionContext, "Headers");

        Dictionary input;
        if (!isUndefinedOrNull(info[0]) && !info[0]->IsObject()) {
            exceptionState.throwTypeError("parameter 1 ('input') is not an object.");

            return;
        }
        input = Dictionary(info.GetIsolate(), info[0], exceptionState);
        if (exceptionState.hadException())
            return;

        Headers* impl = Headers::create(input, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8::Local<v8::Object> wrapper = info.Holder();
        wrapper = impl->associateWithWrapper(info.GetIsolate(), &V8Headers::wrapperTypeInfo, wrapper);
        v8SetReturnValue(info, wrapper);
    }

    static void constructor4(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ConstructionContext, "Headers");

        Vector<Vector<String>> input;
        input = toImplArray<Vector<Vector<String>>>(info[0], 1, info.GetIsolate(), exceptionState);
        if (exceptionState.hadException())
            return;

        Headers* impl = Headers::create(input, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8::Local<v8::Object> wrapper = info.Holder();
        wrapper = impl->associateWithWrapper(info.GetIsolate(), &V8Headers::wrapperTypeInfo, wrapper);
        v8SetReturnValue(info, wrapper);
    }

    static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ConstructionContext, "Headers");
        switch (std::min(1, info.Length())) {
        case 0:
            if (true) {
                HeadersV8Internal::constructor1(info);
                return;
            }
            break;
        case 1:
            if (V8Headers::hasInstance(info[0], info.GetIsolate())) {
                HeadersV8Internal::constructor2(info);
                return;
            }
            if (info[0]->IsArray()) {
                HeadersV8Internal::constructor4(info);
                return;
            }
            if (info[0]->IsObject()) {
                HeadersV8Internal::constructor3(info);
                return;
            }
            break;
        default:
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(0, info.Length()));
            return;
        }
        exceptionState.throwTypeError("No matching constructor signature.");
    }

} // namespace HeadersV8Internal

const V8DOMConfiguration::MethodConfiguration V8HeadersMethods[] = {
    { "append", HeadersV8Internal::appendMethodCallback, 0, 2, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "delete", HeadersV8Internal::deleteMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "get", HeadersV8Internal::getMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "getAll", HeadersV8Internal::getAllMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "has", HeadersV8Internal::hasMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "set", HeadersV8Internal::setMethodCallback, 0, 2, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "keys", HeadersV8Internal::keysMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "values", HeadersV8Internal::valuesMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "entries", HeadersV8Internal::entriesMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "forEach", HeadersV8Internal::forEachMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

void V8Headers::constructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (!info.IsConstructCall()) {
        V8ThrowException::throwTypeError(info.GetIsolate(), ExceptionMessages::constructorNotCallableAsFunction("Headers"));
        return;
    }

    if (ConstructorMode::current(info.GetIsolate()) == ConstructorMode::WrapExistingObject) {
        v8SetReturnValue(info, info.Holder());
        return;
    }

    HeadersV8Internal::constructor(info);
}

static void installV8HeadersTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8Headers::wrapperTypeInfo.interfaceName, v8::Local<v8::FunctionTemplate>(), V8Headers::internalFieldCount);
    interfaceTemplate->SetCallHandler(V8Headers::constructorCallback);
    interfaceTemplate->SetLength(0);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8HeadersMethods, WTF_ARRAY_LENGTH(V8HeadersMethods));

    // Iterator (@@iterator)
    const V8DOMConfiguration::SymbolKeyedMethodConfiguration symbolKeyedIteratorConfiguration = { v8::Symbol::GetIterator, HeadersV8Internal::iteratorMethodCallback, 0, v8::DontEnum, V8DOMConfiguration::OnPrototype };
    V8DOMConfiguration::installMethod(isolate, world, prototypeTemplate, signature, symbolKeyedIteratorConfiguration);
}

v8::Local<v8::FunctionTemplate> V8Headers::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8HeadersTemplate);
}

bool V8Headers::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8Headers::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

Headers* V8Headers::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
