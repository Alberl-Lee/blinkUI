// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/interface.cpp.tmpl

// clang-format on
#include "V8IDBDatabase.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/GeneratedCodeHelper.h"
#include "bindings/core/v8/ScriptState.h"
#include "bindings/core/v8/V8AbstractEventListener.h"
#include "bindings/core/v8/V8DOMConfiguration.h"
#include "bindings/core/v8/V8DOMStringList.h"
#include "bindings/core/v8/V8EventListenerHelper.h"
#include "bindings/core/v8/V8HiddenValue.h"
#include "bindings/core/v8/V8ObjectConstructor.h"
#include "bindings/modules/v8/StringOrStringSequenceOrDOMStringList.h"
#include "bindings/modules/v8/V8IDBObjectStore.h"
#include "bindings/modules/v8/V8IDBObjectStoreParameters.h"
#include "bindings/modules/v8/V8IDBTransaction.h"
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
const WrapperTypeInfo V8IDBDatabase::wrapperTypeInfo = { gin::kEmbedderBlink, V8IDBDatabase::domTemplate, V8IDBDatabase::trace, V8IDBDatabase::traceWrappers, 0, nullptr, "IDBDatabase", &V8EventTarget::wrapperTypeInfo, WrapperTypeInfo::WrapperTypeObjectPrototype, WrapperTypeInfo::ObjectClassId, WrapperTypeInfo::InheritFromActiveScriptWrappable, WrapperTypeInfo::InheritFromEventTarget, WrapperTypeInfo::Dependent };
#if defined(COMPONENT_BUILD) && defined(WIN32) && COMPILER(CLANG)
#pragma clang diagnostic pop
#endif

// This static member must be declared by DEFINE_WRAPPERTYPEINFO in IDBDatabase.h.
// For details, see the comment of DEFINE_WRAPPERTYPEINFO in
// bindings/core/v8/ScriptWrappable.h.
const WrapperTypeInfo& IDBDatabase::s_wrapperTypeInfo = V8IDBDatabase::wrapperTypeInfo;

// [ActiveScriptWrappable]
static_assert(
    std::is_base_of<ActiveScriptWrappableBase, IDBDatabase>::value,
    "IDBDatabase does not inherit from ActiveScriptWrappable<>, but specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");
static_assert(
    !std::is_same<decltype(&IDBDatabase::hasPendingActivity),
        decltype(&ScriptWrappable::hasPendingActivity)>::value,
    "IDBDatabase is not overriding hasPendingActivity(), but is specifying "
    "[ActiveScriptWrappable] extended attribute in the IDL file.  "
    "Be consistent.");

namespace IDBDatabaseV8Internal {

    static void nameAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        v8SetReturnValueString(info, impl->name(), info.GetIsolate());
    }

    MODULES_EXPORT void nameAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::nameAttributeGetter(info);
    }

    static void versionAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        v8SetReturnValue(info, static_cast<double>(impl->version()));
    }

    MODULES_EXPORT void versionAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::versionAttributeGetter(info);
    }

    static void objectStoreNamesAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        DOMStringList* cppValue(WTF::getPtr(impl->objectStoreNames()));

        // Keep the wrapper object for the return value alive as long as |this|
        // object is alive in order to save creation time of the wrapper object.
        if (cppValue && DOMDataStore::setReturnValue(info.GetReturnValue(), cppValue))
            return;
        v8::Local<v8::Value> v8Value(ToV8(cppValue, holder, info.GetIsolate()));
        const char kKeepAliveKey[] = "KeepAlive#IDBDatabase#objectStoreNames";
        V8HiddenValue::setHiddenValue(ScriptState::current(info.GetIsolate()), holder, v8AtomicString(info.GetIsolate(), StringView(kKeepAliveKey, sizeof kKeepAliveKey)), v8Value);

        v8SetReturnValue(info, v8Value);
    }

    MODULES_EXPORT void objectStoreNamesAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::objectStoreNamesAttributeGetter(info);
    }

    static void onabortAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        EventListener* cppValue(WTF::getPtr(impl->onabort()));

        v8SetReturnValue(info, cppValue ? V8AbstractEventListener::cast(cppValue)->getListenerOrNull(info.GetIsolate(), impl->getExecutionContext()) : v8::Null(info.GetIsolate()).As<v8::Value>());
    }

    MODULES_EXPORT void onabortAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::onabortAttributeGetter(info);
    }

    static void onabortAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        // Prepare the value to be set.
        moveEventListenerToNewWrapper(info.GetIsolate(), holder, impl->onabort(), v8Value, V8IDBDatabase::eventListenerCacheIndex);

        impl->setOnabort(V8EventListenerHelper::getEventListener(ScriptState::forReceiverObject(info), v8Value, true, ListenerFindOrCreate));
    }

    MODULES_EXPORT void onabortAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        IDBDatabaseV8Internal::onabortAttributeSetter(v8Value, info);
    }

    static void oncloseAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        EventListener* cppValue(WTF::getPtr(impl->onclose()));

        v8SetReturnValue(info, cppValue ? V8AbstractEventListener::cast(cppValue)->getListenerOrNull(info.GetIsolate(), impl->getExecutionContext()) : v8::Null(info.GetIsolate()).As<v8::Value>());
    }

    MODULES_EXPORT void oncloseAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::oncloseAttributeGetter(info);
    }

    static void oncloseAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        // Prepare the value to be set.
        moveEventListenerToNewWrapper(info.GetIsolate(), holder, impl->onclose(), v8Value, V8IDBDatabase::eventListenerCacheIndex);

        impl->setOnclose(V8EventListenerHelper::getEventListener(ScriptState::forReceiverObject(info), v8Value, true, ListenerFindOrCreate));
    }

    MODULES_EXPORT void oncloseAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        IDBDatabaseV8Internal::oncloseAttributeSetter(v8Value, info);
    }

    static void onerrorAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        EventListener* cppValue(WTF::getPtr(impl->onerror()));

        v8SetReturnValue(info, cppValue ? V8AbstractEventListener::cast(cppValue)->getListenerOrNull(info.GetIsolate(), impl->getExecutionContext()) : v8::Null(info.GetIsolate()).As<v8::Value>());
    }

    MODULES_EXPORT void onerrorAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::onerrorAttributeGetter(info);
    }

    static void onerrorAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        // Prepare the value to be set.
        moveEventListenerToNewWrapper(info.GetIsolate(), holder, impl->onerror(), v8Value, V8IDBDatabase::eventListenerCacheIndex);

        impl->setOnerror(V8EventListenerHelper::getEventListener(ScriptState::forReceiverObject(info), v8Value, true, ListenerFindOrCreate));
    }

    MODULES_EXPORT void onerrorAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        IDBDatabaseV8Internal::onerrorAttributeSetter(v8Value, info);
    }

    static void onversionchangeAttributeGetter(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();

        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        EventListener* cppValue(WTF::getPtr(impl->onversionchange()));

        v8SetReturnValue(info, cppValue ? V8AbstractEventListener::cast(cppValue)->getListenerOrNull(info.GetIsolate(), impl->getExecutionContext()) : v8::Null(info.GetIsolate()).As<v8::Value>());
    }

    MODULES_EXPORT void onversionchangeAttributeGetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::onversionchangeAttributeGetter(info);
    }

    static void onversionchangeAttributeSetter(v8::Local<v8::Value> v8Value, const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Object> holder = info.Holder();
        IDBDatabase* impl = V8IDBDatabase::toImpl(holder);

        // Prepare the value to be set.
        moveEventListenerToNewWrapper(info.GetIsolate(), holder, impl->onversionchange(), v8Value, V8IDBDatabase::eventListenerCacheIndex);

        impl->setOnversionchange(V8EventListenerHelper::getEventListener(ScriptState::forReceiverObject(info), v8Value, true, ListenerFindOrCreate));
    }

    MODULES_EXPORT void onversionchangeAttributeSetterCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        v8::Local<v8::Value> v8Value = info[0];

        IDBDatabaseV8Internal::onversionchangeAttributeSetter(v8Value, info);
    }

    static void createObjectStoreMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "IDBDatabase", "createObjectStore");

        IDBDatabase* impl = V8IDBDatabase::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> name;
        IDBObjectStoreParameters options;
        name = info[0];
        if (!name.prepare())
            return;

        if (!isUndefinedOrNull(info[1]) && !info[1]->IsObject()) {
            exceptionState.throwTypeError("parameter 2 ('options') is not an object.");

            return;
        }
        V8IDBObjectStoreParameters::toImpl(info.GetIsolate(), info[1], options, exceptionState);
        if (exceptionState.hadException())
            return;

        IDBObjectStore* result = impl->createObjectStore(name, options, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void createObjectStoreMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::createObjectStoreMethod(info);
    }

    static void deleteObjectStoreMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "IDBDatabase", "deleteObjectStore");

        IDBDatabase* impl = V8IDBDatabase::toImpl(info.Holder());

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        V8StringResource<> name;
        name = info[0];
        if (!name.prepare())
            return;

        impl->deleteObjectStore(name, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
    }

    MODULES_EXPORT void deleteObjectStoreMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::deleteObjectStoreMethod(info);
    }

    static void transactionMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        ExceptionState exceptionState(info.GetIsolate(), ExceptionState::ExecutionContext, "IDBDatabase", "transaction");

        IDBDatabase* impl = V8IDBDatabase::toImpl(info.Holder());

        ScriptState* scriptState = ScriptState::forReceiverObject(info);

        if (UNLIKELY(info.Length() < 1)) {
            exceptionState.throwTypeError(ExceptionMessages::notEnoughArguments(1, info.Length()));
            return;
        }

        StringOrStringSequenceOrDOMStringList storeNames;
        V8StringResource<> mode;
        V8StringOrStringSequenceOrDOMStringList::toImpl(info.GetIsolate(), info[0], storeNames, UnionTypeConversionMode::NotNullable, exceptionState);
        if (exceptionState.hadException())
            return;

        if (!info[1]->IsUndefined()) {
            mode = info[1];
            if (!mode.prepare())
                return;
            const char* validModeValues[] = {
                "readonly",
                "readwrite",
                "versionchange",
            };
            if (!isValidEnum(mode, validModeValues, WTF_ARRAY_LENGTH(validModeValues), "IDBTransactionMode", exceptionState)) {
                return;
            }
        } else {
            mode = String("readonly");
        }

        IDBTransaction* result = impl->transaction(scriptState, storeNames, mode, exceptionState);
        if (exceptionState.hadException()) {
            return;
        }
        v8SetReturnValue(info, result);
    }

    MODULES_EXPORT void transactionMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::transactionMethod(info);
    }

    static void closeMethod(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabase* impl = V8IDBDatabase::toImpl(info.Holder());

        impl->close();
    }

    MODULES_EXPORT void closeMethodCallback(const v8::FunctionCallbackInfo<v8::Value>& info)
    {
        IDBDatabaseV8Internal::closeMethod(info);
    }

} // namespace IDBDatabaseV8Internal

const V8DOMConfiguration::AccessorConfiguration V8IDBDatabaseAccessors[] = {
    { "name", IDBDatabaseV8Internal::nameAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "version", IDBDatabaseV8Internal::versionAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "objectStoreNames", IDBDatabaseV8Internal::objectStoreNamesAttributeGetterCallback, 0, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::ReadOnly), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "onabort", IDBDatabaseV8Internal::onabortAttributeGetterCallback, IDBDatabaseV8Internal::onabortAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "onclose", IDBDatabaseV8Internal::oncloseAttributeGetterCallback, IDBDatabaseV8Internal::oncloseAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "onerror", IDBDatabaseV8Internal::onerrorAttributeGetterCallback, IDBDatabaseV8Internal::onerrorAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "onversionchange", IDBDatabaseV8Internal::onversionchangeAttributeGetterCallback, IDBDatabaseV8Internal::onversionchangeAttributeSetterCallback, 0, 0, nullptr, 0, v8::DEFAULT, static_cast<v8::PropertyAttribute>(v8::None), V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

const V8DOMConfiguration::MethodConfiguration V8IDBDatabaseMethods[] = {
    { "createObjectStore", IDBDatabaseV8Internal::createObjectStoreMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "deleteObjectStore", IDBDatabaseV8Internal::deleteObjectStoreMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "transaction", IDBDatabaseV8Internal::transactionMethodCallback, 0, 1, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
    { "close", IDBDatabaseV8Internal::closeMethodCallback, 0, 0, v8::None, V8DOMConfiguration::OnPrototype, V8DOMConfiguration::CheckHolder },
};

static void installV8IDBDatabaseTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world, v8::Local<v8::FunctionTemplate> interfaceTemplate)
{
    // Initialize the interface object's template.
    V8DOMConfiguration::initializeDOMInterfaceTemplate(isolate, interfaceTemplate, V8IDBDatabase::wrapperTypeInfo.interfaceName, V8EventTarget::domTemplate(isolate, world), V8IDBDatabase::internalFieldCount);

    v8::Local<v8::Signature> signature = v8::Signature::New(isolate, interfaceTemplate);
    ALLOW_UNUSED_LOCAL(signature);
    v8::Local<v8::ObjectTemplate> instanceTemplate = interfaceTemplate->InstanceTemplate();
    ALLOW_UNUSED_LOCAL(instanceTemplate);
    v8::Local<v8::ObjectTemplate> prototypeTemplate = interfaceTemplate->PrototypeTemplate();
    ALLOW_UNUSED_LOCAL(prototypeTemplate);

    // Register DOM constants, attributes and operations.
    V8DOMConfiguration::installAccessors(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8IDBDatabaseAccessors, WTF_ARRAY_LENGTH(V8IDBDatabaseAccessors));
    V8DOMConfiguration::installMethods(isolate, world, instanceTemplate, prototypeTemplate, interfaceTemplate, signature, V8IDBDatabaseMethods, WTF_ARRAY_LENGTH(V8IDBDatabaseMethods));
}

v8::Local<v8::FunctionTemplate> V8IDBDatabase::domTemplate(v8::Isolate* isolate, const DOMWrapperWorld& world)
{
    return V8DOMConfiguration::domClassTemplate(isolate, world, const_cast<WrapperTypeInfo*>(&wrapperTypeInfo), installV8IDBDatabaseTemplate);
}

bool V8IDBDatabase::hasInstance(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->hasInstance(&wrapperTypeInfo, v8Value);
}

v8::Local<v8::Object> V8IDBDatabase::findInstanceInPrototypeChain(v8::Local<v8::Value> v8Value, v8::Isolate* isolate)
{
    return V8PerIsolateData::from(isolate)->findInstanceInPrototypeChain(&wrapperTypeInfo, v8Value);
}

IDBDatabase* V8IDBDatabase::toImplWithTypeCheck(v8::Isolate* isolate, v8::Local<v8::Value> value)
{
    return hasInstance(value, isolate) ? toImpl(v8::Local<v8::Object>::Cast(value)) : nullptr;
}

} // namespace blink
