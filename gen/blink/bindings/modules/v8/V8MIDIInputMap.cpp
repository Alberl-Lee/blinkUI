// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8MIDIInputMap.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/ScriptValue.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8Iterator.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "core/dom/Document.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8MIDIInputMap::wrapperTypeInfo = { gin::kEmbedderBlink, V8MIDIInputMap::domTemplate, V8MIDIInputMap::trace, V8MIDIInputMap::traceWrappers, 0, nullptr, "MIDIInputMap", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in MIDIInputMap.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& MIDIInputMap::s_wrapperTypeInfo = V8MIDIInputMap::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, MIDIInputMap>::value,
    "MIDIInputMap inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&MIDIInputMap::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "MIDIInputMap is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace MIDIInputMapV8Internal {

    static void sizeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(holder);

        v8SetReturnValueUnsigned(info, impl->size());
    }

    MODULES_EXPORT void sizeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::sizeAttributeGetter(info);
    }

    static void keysMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "keys");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->keysForBinding(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void keysMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::keysMethod(info);
    }

    static void valuesMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "values");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->valuesForBinding(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void valuesMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::valuesMethod(info);
    }

    static void entriesMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "entries");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->entriesForBinding(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void entriesMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::entriesMethod(info);
    }

    static void forEachMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "forEach");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

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
        MIDIInputMapV8Internal::forEachMethod(info);
    }

    static void hasMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "has");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> key;
        key = info[0];
        if (!key.prepare())
            return;

        bool result = impl->hasForBinding(scriptState, key, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValueBool(info, result);
    }

    MODULES_EXPORT void hasMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::hasMethod(info);
    }

    static void getMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "get");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> key;
        key = info[0];
        if (!key.prepare())
            return;

        ScriptValue result = impl->getForBinding(scriptState, key, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result.v8Value());
    }

    MODULES_EXPORT void getMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::getMethod(info);
    }

    static void iteratorMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "MIDIInputMap", "iterator");

        MIDIInputMap* impl = V8MIDIInputMap::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        Iterator* result = impl->iterator(scriptState, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void iteratorMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        MIDIInputMapV8Internal::iteratorMethod(info);
    }

} // namespace MIDIInputMapV8Internal

const V8DOMConfiguration::AccessorConfiguration V8MIDIInputMapAccessors[] = {
    { "size", MIDIInputMapV8Internal::sizeAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

const V8DOMConfiguration::MethodConfiguration V8MIDIInputMapMethods[] = {
    { "keys", MIDIInputMapV8Internal::keysMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "values", MIDIInputMapV8Internal::valuesMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "entries", MIDIInputMapV8Internal::entriesMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "forEach", MIDIInputMapV8Internal::forEachMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "has", MIDIInputMapV8Internal::hasMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "get", MIDIInputMapV8Internal::getMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

static void installV8MIDIInputMapTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8MIDIInputMap::wrapperTypeInfo.interfaceName, v8::Local<v8::FunctionTemplate>(), V8MIDIInputMap::internalFieldCount);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8MIDIInputMapAccessors, WTF_ARRAY_LENGTH(V8MIDIInputMapAccessors));
    V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8MIDIInputMapMethods, WTF_ARRAY_LENGTH(V8MIDIInputMapMethods));

    // Iterator (@@iterator)
    const V8DOMConfiguration::SymbolKeyedMethodConfiguration symbolKeyedIteratorConfiguration = { v8::Symbol::GetIterator, MIDIInputMapV8Internal::iteratorMethodCallback, 0, v8::DontEnum, V8DOMConfiguration::OnPrototype };
    V8DOMConfiguration::installMethod(isolate, world, prototypeTemplate, signature, symbolKeyedIteratorConfiguration);
}

v8::Local<v8::FunctionTemplate> V8MIDIInputMap::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8MIDIInputMapTemplate);
}

bool V8MIDIInputMap::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8MIDIInputMap::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

MIDIInputMap* V8MIDIInputMap::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
