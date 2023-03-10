// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_v8.cpp.tmpl

// clang-format on
#include "V8FaceDetectorOptions.h"

#include "bindings/core/v8/ExceptionState.h"

namespace blink {

void V8FaceDetectorOptions::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, FaceDetectorOptions& impl, ExceptionState& exceptionState)
{
    if (isUndefinedOrNull(v8Value)) {
        return;
    }
    if (!v8Value->IsObject()) {
        exceptionState.throwTypeError("cannot convert to dictionary.");
        return;
    }

    v8::TryCatch block(isolate);
    v8::Local<v8::Object> v8Object;
    if (!v8Call(v8Value->ToObject(isolate->GetCurrentContext()), v8Object, block)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    v8::Local<v8::Value> fastModeValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "fastMode")).ToLocal(&fastModeValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (fastModeValue.IsEmpty() || fastModeValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool fastMode = toBoolean(isolate, fastModeValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setFastMode(fastMode);
    }

    v8::Local<v8::Value> maxDetectedFacesValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "maxDetectedFaces")).ToLocal(&maxDetectedFacesValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (maxDetectedFacesValue.IsEmpty() || maxDetectedFacesValue->IsUndefined()) {
        // Do nothing.
    } else {
        unsigned maxDetectedFaces = toUInt16(isolate, maxDetectedFacesValue, NormalConversion, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setMaxDetectedFaces(maxDetectedFaces);
    }
}

v8::Local<v8::Value> FaceDetectorOptions::toV8Impl(v8::Local<v8::Object> creationContext, v8::Isolate* isolate) const
{
    v8::Local<v8::Object> v8Object = v8::Object::New(isolate);
    if (!toV8FaceDetectorOptions(*this, v8Object, creationContext, isolate))
        return v8::Undefined(isolate);
    return v8Object;
}

bool toV8FaceDetectorOptions(const FaceDetectorOptions& impl, v8::Local<v8::Object> dictionary, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    if (impl.hasFastMode()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "fastMode"), v8Boolean(impl.fastMode(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "fastMode"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasMaxDetectedFaces()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "maxDetectedFaces"), v8::Integer::NewFromUnsigned(isolate, impl.maxDetectedFaces()))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "maxDetectedFaces"), v8::Integer::NewFromUnsigned(isolate, 10u))))
            return false;
    }

    return true;
}

FaceDetectorOptions NativeValueTraits<FaceDetectorOptions>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    FaceDetectorOptions impl;
    V8FaceDetectorOptions::toImpl(isolate, value, impl, exceptionState);
    return impl;
}

} // namespace blink
