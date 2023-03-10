// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8SpeechGrammarList.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/modules/v8/V8SpeechGrammar.h"
#include "core/dom/Document.h"
#include "core/frame/LocalDOMWindow.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8SpeechGrammarList::wrapperTypeInfo = { gin::kEmbedderBlink, V8SpeechGrammarList::domTemplate, V8SpeechGrammarList::trace, V8SpeechGrammarList::traceWrappers, 0, nullptr, "SpeechGrammarList", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in SpeechGrammarList.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& SpeechGrammarList::s_wrapperTypeInfo = V8SpeechGrammarList::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, SpeechGrammarList>::value,
    "SpeechGrammarList inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&SpeechGrammarList::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "SpeechGrammarList is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace SpeechGrammarListV8Internal {

    static void lengthAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        SpeechGrammarList* impl = V8SpeechGrammarList::toImpl(holder);

        v8SetReturnValueUnsigned(info, impl->length());
    }

    MODULES_EXPORT void lengthAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarListV8Internal::lengthAttributeGetter(info);
    }

    static void itemMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "SpeechGrammarList", "item");

        SpeechGrammarList* impl = V8SpeechGrammarList::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        unsigned index;
        index = toUInt32(info.GetIsolate(), info[0], NormalConversion, exceptionState);
        if (exceptionState.hadException())
            return;

        v8SetReturnValue(info, impl->item(index));
    }

    MODULES_EXPORT void itemMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarListV8Internal::itemMethod(info);
    }

    static void addFromUriMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "SpeechGrammarList", "addFromUri");

        SpeechGrammarList* impl = V8SpeechGrammarList::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> src;
        float weight;
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        src = info[0];
        if (!src.prepare())
            return;

        if (UNLIKELY(numArgsPassed <= 1)) {
            impl->addFromUri(scriptState, src);
            return;
        }
        weight = toRestrictedFloat(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.hadException())
            return;

        impl->addFromUri(scriptState, src, weight);
    }

    MODULES_EXPORT void addFromUriMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarListV8Internal::addFromUriMethod(info);
    }

    static void addFromStringMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "SpeechGrammarList", "addFromString");

        SpeechGrammarList* impl = V8SpeechGrammarList::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> string;
        float weight;
        int numArgsPassed = info.Length();
        while (numArgsPassed > 0) {
            if (!info[numArgsPassed - 1]->IsUndefined())
                break;
            --numArgsPassed;
        }
        string = info[0];
        if (!string.prepare())
            return;

        if (UNLIKELY(numArgsPassed <= 1)) {
            impl->addFromString(string);
            return;
        }
        weight = toRestrictedFloat(info.GetIsolate(), info[1], exceptionState);
        if (exceptionState.hadException())
            return;

        impl->addFromString(string, weight);
    }

    MODULES_EXPORT void addFromStringMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarListV8Internal::addFromStringMethod(info);
    }

    static void constructor(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarList* impl = SpeechGrammarList::create();
        v8::Local<v8::Object> wrapper = info.Holder();
        wrapper = impl->associateWithWrapper(info.GetIsolate(), &V8SpeechGrammarList::wrapperTypeInfo, wrapper);
        v8SetReturnValue(info, wrapper);
    }

    static void indexedPropertyGetter(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarList* impl = V8SpeechGrammarList::toImpl(info.Holder());

        // We assume that all the implementations support length() method, although
        // the spec doesn't require that length() must exist.  It's okay that
        // the interface does not have length attribute as long as the
        // implementation supports length() member function.
        if (index >= impl->length())
            return; // Returns undefined due to out-of-range.

        SpeechGrammar* result = impl->item(index);
        v8SetReturnValueFast(info, result, impl);
    }

    MODULES_EXPORT void indexedPropertyGetterCallback(uint32_t index, const v8::PropertyCallbackInfo<v8::Value>& info)
    {
        SpeechGrammarListV8Internal::indexedPropertyGetter(index, info);
    }

} // namespace SpeechGrammarListV8Internal

const V8DOMConfiguration::AccessorConfiguration V8SpeechGrammarListAccessors[] = {
    { "length", SpeechGrammarListV8Internal::lengthAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

const V8DOMConfiguration::MethodConfiguration V8SpeechGrammarListMethods[] = {
    { "item", SpeechGrammarListV8Internal::itemMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "addFromUri", SpeechGrammarListV8Internal::addFromUriMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "addFromString", SpeechGrammarListV8Internal::addFromStringMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

void V8SpeechGrammarList::constructorCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
{
    if (!info.IsConstructCall()) {
        V8ThrowException::throwTypeError(info.GetIsolate(), ExceptionMessages::constructorNotCallableAsFunction("SpeechGrammarList"));
        return;
    }

    if (ConstructorMode::current(info.GetIsolate()) == ConstructorMode::WrapExistingObject) {
        v8SetReturnValue(info, info.Holder());
        return;
    }

    SpeechGrammarListV8Internal::constructor(info);
}

static void installV8SpeechGrammarListTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8SpeechGrammarList::wrapperTypeInfo.interfaceName, v8::Local<v8::FunctionTemplate>(), V8SpeechGrammarList::internalFieldCount);
    interfaceTemplate->SetCallHandler(V8SpeechGrammarList::constructorCallback);
    interfaceTemplate->SetLength(0);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8SpeechGrammarListAccessors, WTF_ARRAY_LENGTH(V8SpeechGrammarListAccessors));
    V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8SpeechGrammarListMethods, WTF_ARRAY_LENGTH(V8SpeechGrammarListMethods));

    // Indexed properties
    v8::IndexedPropertyHandlerConfiguration indexedPropertyHandlerConfig(SpeechGrammarListV8Internal::indexedPropertyGetterCallback, 0, 0, 0, indexedPropertyEnumerator<SpeechGrammarList>, v8::Local<v8::Value>(), v8::PropertyHandlerFlags::kNone);
    instanceTemplate->SetHandler(indexedPropertyHandlerConfig);

    // Array iterator (@@iterator)
    prototypeTemplate->SetIntrinsicDataProperty(v8::Symbol::GetIterator(isolate), v8::kArrayProto_values, v8::DontEnum);
}

v8::Local<v8::FunctionTemplate> V8SpeechGrammarList::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8SpeechGrammarListTemplate);
}

bool V8SpeechGrammarList::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8SpeechGrammarList::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

SpeechGrammarList* V8SpeechGrammarList::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
