// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8CSSTransformComponent.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/V8CSSMatrixTransformComponent.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "core/dom/Document.h"
#include "platform/RuntimeEnabledFeatures.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8CSSTransformComponent::wrapperTypeInfo = { gin::kEmbedderBlink, V8CSSTransformComponent::domTemplate, V8CSSTransformComponent::trace, V8CSSTransformComponent::traceWrappers, 0, nullptr, "CSSTransformComponent", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in CSSTransformComponent.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& CSSTransformComponent::s_wrapperTypeInfo = V8CSSTransformComponent::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, CSSTransformComponent>::value,
    "CSSTransformComponent inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&CSSTransformComponent::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "CSSTransformComponent is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace CSSTransformComponentV8Internal {

    static void cssTextAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        CSSTransformComponent* impl = V8CSSTransformComponent::toImpl(holder);

        v8SetReturnValueString(info, impl->cssText(), info.GetIsolate());
    }

    CORE_EXPORT void cssTextAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        CSSTransformComponentV8Internal::cssTextAttributeGetter(info);
    }

    static void is2DMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        CSSTransformComponent* impl = V8CSSTransformComponent::toImpl(info.Holder());

        v8SetReturnValueBool(info, impl->is2D());
    }

    CORE_EXPORT void is2DMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        CSSTransformComponentV8Internal::is2DMethod(info);
    }

    static void asMatrixMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        CSSTransformComponent* impl = V8CSSTransformComponent::toImpl(info.Holder());

        v8SetReturnValue(info, impl->asMatrix());
    }

    CORE_EXPORT void asMatrixMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        CSSTransformComponentV8Internal::asMatrixMethod(info);
    }

} // namespace CSSTransformComponentV8Internal

const V8DOMConfiguration::AccessorConfiguration V8CSSTransformComponentAccessors[] = {
    { "cssText", CSSTransformComponentV8Internal::cssTextAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

const V8DOMConfiguration::MethodConfiguration V8CSSTransformComponentMethods[] = {
    { "is2D", CSSTransformComponentV8Internal::is2DMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "asMatrix", CSSTransformComponentV8Internal::asMatrixMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

static void installV8CSSTransformComponentTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8CSSTransformComponent::wrapperTypeInfo.interfaceName, v8::Local<v8::FunctionTemplate>(), V8CSSTransformComponent::internalFieldCount);

    if (!RuntimeEnabledFeatures::cssTypedOMEnabled()) {
        return;
    }

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8CSSTransformComponentAccessors, WTF_ARRAY_LENGTH(V8CSSTransformComponentAccessors));
    V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8CSSTransformComponentMethods, WTF_ARRAY_LENGTH(V8CSSTransformComponentMethods));
}

v8::Local<v8::FunctionTemplate> V8CSSTransformComponent::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8CSSTransformComponentTemplate);
}

bool V8CSSTransformComponent::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8CSSTransformComponent::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

CSSTransformComponent* V8CSSTransformComponent::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
