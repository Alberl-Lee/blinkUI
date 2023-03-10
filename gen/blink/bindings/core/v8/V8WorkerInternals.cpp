// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8WorkerInternals.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/core/v8/V8OriginTrialsTest.h"
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
WrapperTypeInfo V8WorkerInternals::wrapperTypeInfo = { gin::kEmbedderBlink, V8WorkerInternals::domTemplate, V8WorkerInternals::trace, V8WorkerInternals::traceWrappers, 0, nullptr, "WorkerInternals", 0, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::NotInheritFromActiveScriptWrappable, WrapperTypeInfo::NotInheritFromEventTarget, WrapperTypeInfo::Independent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in WorkerInternals.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& WorkerInternals::s_wrapperTypeInfo = V8WorkerInternals::wrapperTypeInfo;

// not [ActiveScriptWrappable]
static_assert(
    !std::is_base_of<ActiveScriptWrappableBase, WorkerInternals>::value,
    "WorkerInternals inherits from ActiveScriptWrappable<>, but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    std::is_same<decltype(&WorkerInternals::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "WorkerInternals is overriding hasPendingActivity(), but is not specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

WorkerInternals::~WorkerInternals()
{
    DebugBreak();
}

OriginTrialsTest* WorkerInternals::originTrialsTest() const
{
    DebugBreak();
    return nullptr;
}

namespace WorkerInternalsV8Internal {

    static void originTrialsTestMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        WorkerInternals* impl = V8WorkerInternals::toImpl(info.Holder());

        v8SetReturnValue(info, impl->originTrialsTest());
    }

    void originTrialsTestMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        WorkerInternalsV8Internal::originTrialsTestMethod(info);
    }

} // namespace WorkerInternalsV8Internal

const V8DOMConfiguration::MethodConfiguration V8WorkerInternalsMethods[] = {
    { "originTrialsTest", WorkerInternalsV8Internal::originTrialsTestMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

void V8WorkerInternals::installV8WorkerInternalsTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8WorkerInternals::wrapperTypeInfo.interfaceName, v8::Local<v8::FunctionTemplate>(), V8WorkerInternals::internalFieldCount);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8WorkerInternalsMethods, WTF_ARRAY_LENGTH(V8WorkerInternalsMethods));
}

v8::Local<v8::FunctionTemplate> V8WorkerInternals::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), V8WorkerInternals::installV8WorkerInternalsTemplateFunction);
}

bool V8WorkerInternals::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8WorkerInternals::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

WorkerInternals* V8WorkerInternals::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

InstallTemplateFunction V8WorkerInternals::installV8WorkerInternalsTemplateFunction = (InstallTemplateFunction)&V8WorkerInternals::installV8WorkerInternalsTemplate;

void V8WorkerInternals::updateWrapperTypeInfo(InstallTemplateFunction installTemplateFunction, PreparePrototypeAndInterfaceObjectFunction preparePrototypeAndInterfaceObjectFunction)
{
    V8WorkerInternals::installV8WorkerInternalsTemplateFunction = installTemplateFunction;
    if (preparePrototypeAndInterfaceObjectFunction)
        V8WorkerInternals::wrapperTypeInfo.preparePrototypeAndInterfaceObjectFunction = preparePrototypeAndInterfaceObjectFunction;
}

} // namespace blink
