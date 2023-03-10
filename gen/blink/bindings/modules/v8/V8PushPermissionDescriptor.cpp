// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_v8.cpp.tmpl

// clang-format on
#include "V8PushPermissionDescriptor.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/modules/v8/V8PermissionDescriptor.h"

namespace blink {

void V8PushPermissionDescriptor::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, PushPermissionDescriptor& impl, ExceptionState& exceptionState)
{
    if (isUndefinedOrNull(v8Value)) {
        return;
    }
    if (!v8Value->IsObject()) {
        exceptionState.throwTypeError("cannot convert to dictionary.");
        return;
    }

    V8PermissionDescriptor::toImpl(isolate, v8Value, impl, exceptionState);
    if (exceptionState.hadException())
        return;

    v8::TryCatch block(isolate);
    v8::Local<v8::Object> v8Object;
    if (!v8Call(v8Value->ToObject(isolate->GetCurrentContext()), v8Object, block)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    v8::Local<v8::Value> userVisibleOnlyValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "userVisibleOnly")).ToLocal(&userVisibleOnlyValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (userVisibleOnlyValue.IsEmpty() || userVisibleOnlyValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool userVisibleOnly = toBoolean(isolate, userVisibleOnlyValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setUserVisibleOnly(userVisibleOnly);
    }
}

v8::Local<v8::Value> PushPermissionDescriptor::toV8Impl(v8::Local<v8::Object> creationContext, v8::Isolate* isolate) const
{
    v8::Local<v8::Object> v8Object = v8::Object::New(isolate);
    if (!toV8PushPermissionDescriptor(*this, v8Object, creationContext, isolate))
        return v8::Undefined(isolate);
    return v8Object;
}

bool toV8PushPermissionDescriptor(const PushPermissionDescriptor& impl, v8::Local<v8::Object> dictionary, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    if (!toV8PermissionDescriptor(impl, dictionary, creationContext, isolate))
        return false;

    if (impl.hasUserVisibleOnly()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "userVisibleOnly"), v8Boolean(impl.userVisibleOnly(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "userVisibleOnly"), v8Boolean(false, isolate))))
            return false;
    }

    return true;
}

PushPermissionDescriptor NativeValueTraits<PushPermissionDescriptor>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    PushPermissionDescriptor impl;
    V8PushPermissionDescriptor::toImpl(isolate, value, impl, exceptionState);
    return impl;
}

} // namespace blink
