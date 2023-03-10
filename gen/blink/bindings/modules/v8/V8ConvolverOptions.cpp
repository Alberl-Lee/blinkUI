// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_v8.cpp.tmpl

// clang-format on
#include "V8ConvolverOptions.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/modules/v8/V8AudioBuffer.h"
#include "bindings/modules/v8/V8AudioNodeOptions.h"

namespace blink {

void V8ConvolverOptions::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, ConvolverOptions& impl, ExceptionState& exceptionState)
{
    if (isUndefinedOrNull(v8Value)) {
        return;
    }
    if (!v8Value->IsObject()) {
        exceptionState.throwTypeError("cannot convert to dictionary.");
        return;
    }

    V8AudioNodeOptions::toImpl(isolate, v8Value, impl, exceptionState);
    if (exceptionState.hadException())
        return;

    v8::TryCatch block(isolate);
    v8::Local<v8::Object> v8Object;
    if (!v8Call(v8Value->ToObject(isolate->GetCurrentContext()), v8Object, block)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    v8::Local<v8::Value> bufferValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "buffer")).ToLocal(&bufferValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (bufferValue.IsEmpty() || bufferValue->IsUndefined()) {
        // Do nothing.
    } else if (bufferValue->IsNull()) {
        impl.setBufferToNull();
    } else {
        AudioBuffer* buffer = V8AudioBuffer::toImplWithTypeCheck(isolate, bufferValue);
        if (!buffer) {
            exceptionState.throwTypeError("member buffer is not of type AudioBuffer.");
            return;
        }
        impl.setBuffer(buffer);
    }

    v8::Local<v8::Value> disableNormalizationValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "disableNormalization")).ToLocal(&disableNormalizationValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (disableNormalizationValue.IsEmpty() || disableNormalizationValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool disableNormalization = toBoolean(isolate, disableNormalizationValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setDisableNormalization(disableNormalization);
    }
}

v8::Local<v8::Value> ConvolverOptions::toV8Impl(v8::Local<v8::Object> creationContext, v8::Isolate* isolate) const
{
    v8::Local<v8::Object> v8Object = v8::Object::New(isolate);
    if (!toV8ConvolverOptions(*this, v8Object, creationContext, isolate))
        return v8::Undefined(isolate);
    return v8Object;
}

bool toV8ConvolverOptions(const ConvolverOptions& impl, v8::Local<v8::Object> dictionary, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    if (!toV8AudioNodeOptions(impl, dictionary, creationContext, isolate))
        return false;

    if (impl.hasBuffer()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "buffer"), ToV8(impl.buffer(), creationContext, isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "buffer"), v8::Null(isolate))))
            return false;
    }

    if (impl.hasDisableNormalization()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "disableNormalization"), v8Boolean(impl.disableNormalization(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "disableNormalization"), v8Boolean(false, isolate))))
            return false;
    }

    return true;
}

ConvolverOptions NativeValueTraits<ConvolverOptions>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    ConvolverOptions impl;
    V8ConvolverOptions::toImpl(isolate, value, impl, exceptionState);
    return impl;
}

} // namespace blink
