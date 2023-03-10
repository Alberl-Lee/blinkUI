// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8PhotoCapabilities.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8HiddenValue.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/modules/v8/V8MediaSettingsRange.h"
#include "core/dom/Document.h"
#include "core/inspector/ConsoleMessage.h"
#include "wtf/GetPtr.h"
#include "wtf/RefPtr.h"

namespace blink {

// Suppress warning: global constructors, because struct WrapperTypeInfo is trivial
// and does not depend on another global objects.
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wglobal-constructors"
#endif
const WrapperTypeInfo V8PhotoCapabilities::wrapperTypeInfo = { gin::kEmbedderBlink, V8PhotoCapabilities::domTemplate, V8PhotoCapabilities::trace, V8PhotoCapabilities::traceWrappers, 0, nullptr, "PhotoCapabilities", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in PhotoCapabilities.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& PhotoCapabilities::s_wrapperTypeInfo = V8PhotoCapabilities::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, PhotoCapabilities>::value,
    "PhotoCapabilities inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&PhotoCapabilities::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "PhotoCapabilities is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace PhotoCapabilitiesV8Internal {

    static void whiteBalanceModeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        v8SetReturnValueString(info, impl->whiteBalanceMode(), info.GetIsolate());
    }

    MODULES_EXPORT void whiteBalanceModeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::whiteBalanceModeAttributeGetter(info);
    }

    static void colorTemperatureAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->colorTemperature()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#colorTemperature";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void colorTemperatureAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::colorTemperatureAttributeGetter(info);
    }

    static void exposureModeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        v8SetReturnValueString(info, impl->exposureMode(), info.GetIsolate());
    }

    MODULES_EXPORT void exposureModeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::exposureModeAttributeGetter(info);
    }

    static void exposureCompensationAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->exposureCompensation()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#exposureCompensation";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void exposureCompensationAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::exposureCompensationAttributeGetter(info);
    }

    static void isoAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->iso()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#iso";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void isoAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::isoAttributeGetter(info);
    }

    static void redEyeReductionAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        v8SetReturnValueBool(info, impl->redEyeReduction());
    }

    MODULES_EXPORT void redEyeReductionAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::redEyeReductionAttributeGetter(info);
    }

    static void focusModeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        v8SetReturnValueString(info, impl->focusMode(), info.GetIsolate());
    }

    MODULES_EXPORT void focusModeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::focusModeAttributeGetter(info);
    }

    static void brightnessAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->brightness()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#brightness";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void brightnessAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::brightnessAttributeGetter(info);
    }

    static void contrastAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->contrast()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#contrast";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void contrastAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::contrastAttributeGetter(info);
    }

    static void saturationAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->saturation()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#saturation";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void saturationAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::saturationAttributeGetter(info);
    }

    static void sharpnessAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->sharpness()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#sharpness";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void sharpnessAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::sharpnessAttributeGetter(info);
    }

    static void imageHeightAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->imageHeight()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#imageHeight";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void imageHeightAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::imageHeightAttributeGetter(info);
    }

    static void imageWidthAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->imageWidth()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#imageWidth";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void imageWidthAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::imageWidthAttributeGetter(info);
    }

    static void zoomAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        MediaSettingsRange* cppValue(WTF::getPtr(impl->zoom()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#PhotoCapabilities#zoom";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void zoomAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::zoomAttributeGetter(info);
    }

    static void fillLightModeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        PhotoCapabilities* impl = V8PhotoCapabilities::toImpl(holder);

        v8SetReturnValueString(info, impl->fillLightMode(), info.GetIsolate());
    }

    MODULES_EXPORT void fillLightModeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        PhotoCapabilitiesV8Internal::fillLightModeAttributeGetter(info);
    }

} // namespace PhotoCapabilitiesV8Internal

const V8DOMConfiguration::AccessorConfiguration V8PhotoCapabilitiesAccessors[] = {
    { "whiteBalanceMode", PhotoCapabilitiesV8Internal::whiteBalanceModeAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "colorTemperature", PhotoCapabilitiesV8Internal::colorTemperatureAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "exposureMode", PhotoCapabilitiesV8Internal::exposureModeAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "exposureCompensation", PhotoCapabilitiesV8Internal::exposureCompensationAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "iso", PhotoCapabilitiesV8Internal::isoAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "redEyeReduction", PhotoCapabilitiesV8Internal::redEyeReductionAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "focusMode", PhotoCapabilitiesV8Internal::focusModeAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "brightness", PhotoCapabilitiesV8Internal::brightnessAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "contrast", PhotoCapabilitiesV8Internal::contrastAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "saturation", PhotoCapabilitiesV8Internal::saturationAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "sharpness", PhotoCapabilitiesV8Internal::sharpnessAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "imageHeight", PhotoCapabilitiesV8Internal::imageHeightAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "imageWidth", PhotoCapabilitiesV8Internal::imageWidthAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "zoom", PhotoCapabilitiesV8Internal::zoomAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "fillLightMode", PhotoCapabilitiesV8Internal::fillLightModeAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

static void installV8PhotoCapabilitiesTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8PhotoCapabilities::wrapperTypeInfo.interfaceName, v8::Local<v8::FunctionTemplate>(), V8PhotoCapabilities::internalFieldCount);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8PhotoCapabilitiesAccessors, WTF_ARRAY_LENGTH(V8PhotoCapabilitiesAccessors));
}

v8::Local<v8::FunctionTemplate> V8PhotoCapabilities::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8PhotoCapabilitiesTemplate);
}

bool V8PhotoCapabilities::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8PhotoCapabilities::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

PhotoCapabilities* V8PhotoCapabilities::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
