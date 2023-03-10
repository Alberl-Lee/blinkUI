// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8HTMLFrameElement.h"

#include "bindings/core/v8/BindingSecurity.h"
#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8Document.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/core/v8/V8Window.h"
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
const WrapperTypeInfo V8HTMLFrameElement::wrapperTypeInfo = { gin::kEmbedderBlink, V8HTMLFrameElement::domTemplate, V8HTMLFrameElement::trace, V8HTMLFrameElement::traceWrappers, 0, nullptr, "HTMLFrameElement", &V8HTMLElement::wrapperTypeInfo, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::NodeClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::InheritFromEventTarget, WrapperTypeInfo::Dependent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in HTMLFrameElement.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& HTMLFrameElement::s_wrapperTypeInfo = V8HTMLFrameElement::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, HTMLFrameElement>::value,
    "HTMLFrameElement inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&HTMLFrameElement::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "HTMLFrameElement is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace HTMLFrameElementV8Internal {

    static void nameAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->getNameAttribute(), info.GetIsolate());
    }

    CORE_EXPORT void nameAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::nameAttributeGetter(info);
    }

    static void nameAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::nameAttr, cppValue);
    }

    CORE_EXPORT void nameAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::nameAttributeSetter(v8Value, info);
    }

    static void scrollingAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->fastGetAttribute(HTMLNames::scrollingAttr), info.GetIsolate());
    }

    CORE_EXPORT void scrollingAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::scrollingAttributeGetter(info);
    }

    static void scrollingAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::scrollingAttr, cppValue);
    }

    CORE_EXPORT void scrollingAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::scrollingAttributeSetter(v8Value, info);
    }

    static void srcAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->getURLAttribute(HTMLNames::srcAttr), info.GetIsolate());
    }

    CORE_EXPORT void srcAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::srcAttributeGetter(info);
    }

    static void srcAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::srcAttr, cppValue);
    }

    CORE_EXPORT void srcAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::srcAttributeSetter(v8Value, info);
    }

    static void frameBorderAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->fastGetAttribute(HTMLNames::frameborderAttr), info.GetIsolate());
    }

    CORE_EXPORT void frameBorderAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::frameBorderAttributeGetter(info);
    }

    static void frameBorderAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::frameborderAttr, cppValue);
    }

    CORE_EXPORT void frameBorderAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::frameBorderAttributeSetter(v8Value, info);
    }

    static void longDescAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->getURLAttribute(HTMLNames::longdescAttr), info.GetIsolate());
    }

    CORE_EXPORT void longDescAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::longDescAttributeGetter(info);
    }

    static void longDescAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::longdescAttr, cppValue);
    }

    CORE_EXPORT void longDescAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::longDescAttributeSetter(v8Value, info);
    }

    static void noResizeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueBool(info, impl->fastHasAttribute(HTMLNames::noresizeAttr));
    }

    CORE_EXPORT void noResizeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::noResizeAttributeGetter(info);
    }

    static void noResizeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Skip on compact node DOMString getters.
        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::SetterContext, "HTMLFrameElement", "noResize");

        // Prepare the value to be set.
        bool cppValue = toBoolean(info.GetIsolate(), v8Value, exceptionState);
        if (exceptionState.hadException())
            return;

        impl->setBooleanAttribute(HTMLNames::noresizeAttr, cppValue);
    }

    CORE_EXPORT void noResizeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::noResizeAttributeSetter(v8Value, info);
    }

    static void contentDocumentAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Perform a security check for the returned object.
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::GetterContext, "HTMLFrameElement", "contentDocument");
        if (!BindingSecurity::shouldAllowAccessTo(currentDOMWindow(info.GetIsolate()), WTF::getPtr(impl->contentDocument()), exceptionState)) {
            v8SetReturnValueNull(info);
            return;
        }

        v8SetReturnValue(info, ToV8(WTF::getPtr(impl->contentDocument()), ToV8(impl->contentWindow(), v8::Local<v8::Object>(), info.GetIsolate()).As<v8::Object>(), info.GetIsolate()));
    }

    CORE_EXPORT void contentDocumentAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::contentDocumentAttributeGetter(info);
    }

    static void contentWindowAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueFast(info, WTF::getPtr(impl->contentWindow()), impl);
    }

    CORE_EXPORT void contentWindowAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::contentWindowAttributeGetter(info);
    }

    static void marginHeightAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->fastGetAttribute(HTMLNames::marginheightAttr), info.GetIsolate());
    }

    CORE_EXPORT void marginHeightAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::marginHeightAttributeGetter(info);
    }

    static void marginHeightAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<TreatNullAsEmptyString> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::marginheightAttr, cppValue);
    }

    CORE_EXPORT void marginHeightAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::marginHeightAttributeSetter(v8Value, info);
    }

    static void marginWidthAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        v8SetReturnValueString(info, impl->fastGetAttribute(HTMLNames::marginwidthAttr), info.GetIsolate());
    }

    CORE_EXPORT void marginWidthAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        HTMLFrameElementV8Internal::marginWidthAttributeGetter(info);
    }

    static void marginWidthAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        HTMLFrameElement* impl = V8HTMLFrameElement::toImpl(holder);

        // Prepare the value to be set.
        V8StringResource<TreatNullAsEmptyString> cppValue = v8Value;
        if (!cppValue.prepare())
            return;

        impl->setAttribute(HTMLNames::marginwidthAttr, cppValue);
    }

    CORE_EXPORT void marginWidthAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        CEReactionsScope ceReactionsScope;

        V0CustomElementProcessingStack::CallbackDeliveryScope deliveryScope;

        HTMLFrameElementV8Internal::marginWidthAttributeSetter(v8Value, info);
    }

} // namespace HTMLFrameElementV8Internal

const V8DOMConfiguration::AccessorConfiguration V8HTMLFrameElementAccessors[] = {
    { "name", HTMLFrameElementV8Internal::nameAttributeGetterCallback, HTMLFrameElementV8Internal::nameAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "scrolling", HTMLFrameElementV8Internal::scrollingAttributeGetterCallback, HTMLFrameElementV8Internal::scrollingAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "src", HTMLFrameElementV8Internal::srcAttributeGetterCallback, HTMLFrameElementV8Internal::srcAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "frameBorder", HTMLFrameElementV8Internal::frameBorderAttributeGetterCallback, HTMLFrameElementV8Internal::frameBorderAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "longDesc", HTMLFrameElementV8Internal::longDescAttributeGetterCallback, HTMLFrameElementV8Internal::longDescAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "noResize", HTMLFrameElementV8Internal::noResizeAttributeGetterCallback, HTMLFrameElementV8Internal::noResizeAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "contentDocument", HTMLFrameElementV8Internal::contentDocumentAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "contentWindow", HTMLFrameElementV8Internal::contentWindowAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "marginHeight", HTMLFrameElementV8Internal::marginHeightAttributeGetterCallback, HTMLFrameElementV8Internal::marginHeightAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "marginWidth", HTMLFrameElementV8Internal::marginWidthAttributeGetterCallback, HTMLFrameElementV8Internal::marginWidthAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

static void installV8HTMLFrameElementTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8HTMLFrameElement::wrapperTypeInfo.interfaceName, V8HTMLElement::domTemplate(isolate, world), V8HTMLFrameElement::internalFieldCount);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8HTMLFrameElementAccessors, WTF_ARRAY_LENGTH(V8HTMLFrameElementAccessors));
}

v8::Local<v8::FunctionTemplate> V8HTMLFrameElement::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8HTMLFrameElementTemplate);
}

bool V8HTMLFrameElement::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8HTMLFrameElement::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

HTMLFrameElement* V8HTMLFrameElement::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
