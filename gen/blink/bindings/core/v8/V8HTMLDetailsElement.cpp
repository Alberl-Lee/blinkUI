// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8HTMLDetailsElement.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "core/HTMLNames.h"
#include "core/animation/ElementAnimation.h"
#include "core/dom/Document.h"
#include "core/dom/ElementFullscreen.h"
#include "core/dom/custom/CEReactionsScope.h"
#include "core/dom/custom/V0CustomElementProcessingStack.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8HTMLDetailsElement::wrapperTypeInfo = { gin::kEmbedderBlink, V8HTMLDetailsElement::domTemplate, V8HTMLDetailsElement::trace, V8HTMLDetailsElement::traceWrappers, 0, nullptr, "HTMLDetailsElement", &V8HTMLElement::wrapperTypeInfo, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::NodeClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::InheritFromEventTarget, WrapperTypeInfo::Dependent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in HTMLDetailsElement.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& HTMLDetailsElement::s_wrapperTypeInfo = V8HTMLDetailsElement::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, HTMLDetailsElement>::value,
    "HTMLDetailsElement inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&HTMLDetailsElement::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "HTMLDetailsElement is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace HTMLDetailsElementV8Internal {

    static void openAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLDetailsElement* impl = V8HTMLDetailsElement::toImpl(holder);

        v8SetReturnValueBool(info, impl->fastHasAttribute(HTMLNames::openAttr));
    }

    CORE_EXPORT void openAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLDetailsElementV8Internal::openAttributeGetter(info);
    }

    static void openAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLDetailsElement* impl = V8HTMLDetailsElement::toImpl(holder);

        // Skip on compact node DOMString getters.
        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::SetterContext, "HTMLDetailsElement", "open");

        // Prepare the value to be set.
        bool cppValue = toBoolean(info.GetIsolate(), v8Value, exceptionState);
        if (exceptionState.hadException())
            return;

        impl->setBooleanAttribute(HTMLNames::openAttr, cppValue);
    }

    CORE_EXPORT void openAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLDetailsElementV8Internal::openAttributeSetter(v8Value, info);
    }

} // namespace HTMLDetailsElementV8Internal

const V8DOMConfiguration::AccessorConfiguration V8HTMLDetailsElementAccessors[] = {
    { "open", HTMLDetailsElementV8Internal::openAttributeGetterCallback, HTMLDetailsElementV8Internal::openAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

static void installV8HTMLDetailsElementTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8HTMLDetailsElement::wrapperTypeInfo.interfaceName, V8HTMLElement::domTemplate(isolate, world), V8HTMLDetailsElement::internalFieldCount);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8HTMLDetailsElementAccessors, WTF_ARRAY_LENGTH(V8HTMLDetailsElementAccessors));
}

v8::Local<v8::FunctionTemplate> V8HTMLDetailsElement::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8HTMLDetailsElementTemplate);
}

bool V8HTMLDetailsElement::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8HTMLDetailsElement::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

HTMLDetailsElement* V8HTMLDetailsElement::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
