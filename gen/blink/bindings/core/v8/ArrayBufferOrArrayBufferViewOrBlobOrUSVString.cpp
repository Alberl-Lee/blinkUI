// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/union_container.cpp.tmpl

// clang-format on
#include "ArrayBufferOrArrayBufferViewOrBlobOrUSVString.h"

#include "bindings/core/v8/ArrayBufferOrArrayBufferViewOrBlobOrUSVString.h"
#include "bindings/core/v8/ToV8.h"
#include "bindings/core/v8/V8ArrayBuffer.h"
#include "bindings/core/v8/V8ArrayBufferView.h"
#include "bindings/core/v8/V8Blob.h"
#include "core/dom/FlexibleArrayBufferView.h"

namespace blink {

ArrayBufferOrArrayBufferViewOrBlobOrUSVString::ArrayBufferOrArrayBufferViewOrBlobOrUSVString()
    : m_type(SpecificTypeNone)
{
}

DOMArrayBuffer* ArrayBufferOrArrayBufferViewOrBlobOrUSVString::getAsArrayBuffer() const
{
    DCHECK(isArrayBuffer());
    return m_arrayBuffer;
}

void ArrayBufferOrArrayBufferViewOrBlobOrUSVString::setArrayBuffer(DOMArrayBuffer* value)
{
    DCHECK(isNull());
    m_arrayBuffer = value;
    m_type = SpecificTypeArrayBuffer;
}

ArrayBufferOrArrayBufferViewOrBlobOrUSVString ArrayBufferOrArrayBufferViewOrBlobOrUSVString::fromArrayBuffer(DOMArrayBuffer* value)
{
    ArrayBufferOrArrayBufferViewOrBlobOrUSVString container;
    container.setArrayBuffer(value);
    return container;
}

DOMArrayBufferView* ArrayBufferOrArrayBufferViewOrBlobOrUSVString::getAsArrayBufferView() const
{
    DCHECK(isArrayBufferView());
    return m_arrayBufferView;
}

void ArrayBufferOrArrayBufferViewOrBlobOrUSVString::setArrayBufferView(DOMArrayBufferView* value)
{
    DCHECK(isNull());
    m_arrayBufferView = value;
    m_type = SpecificTypeArrayBufferView;
}

ArrayBufferOrArrayBufferViewOrBlobOrUSVString ArrayBufferOrArrayBufferViewOrBlobOrUSVString::fromArrayBufferView(DOMArrayBufferView* value)
{
    ArrayBufferOrArrayBufferViewOrBlobOrUSVString container;
    container.setArrayBufferView(value);
    return container;
}

Blob* ArrayBufferOrArrayBufferViewOrBlobOrUSVString::getAsBlob() const
{
    DCHECK(isBlob());
    return m_blob;
}

void ArrayBufferOrArrayBufferViewOrBlobOrUSVString::setBlob(Blob* value)
{
    DCHECK(isNull());
    m_blob = value;
    m_type = SpecificTypeBlob;
}

ArrayBufferOrArrayBufferViewOrBlobOrUSVString ArrayBufferOrArrayBufferViewOrBlobOrUSVString::fromBlob(Blob* value)
{
    ArrayBufferOrArrayBufferViewOrBlobOrUSVString container;
    container.setBlob(value);
    return container;
}

String ArrayBufferOrArrayBufferViewOrBlobOrUSVString::getAsUSVString() const
{
    DCHECK(isUSVString());
    return m_uSVString;
}

void ArrayBufferOrArrayBufferViewOrBlobOrUSVString::setUSVString(String value)
{
    DCHECK(isNull());
    m_uSVString = value;
    m_type = SpecificTypeUSVString;
}

ArrayBufferOrArrayBufferViewOrBlobOrUSVString ArrayBufferOrArrayBufferViewOrBlobOrUSVString::fromUSVString(String value)
{
    ArrayBufferOrArrayBufferViewOrBlobOrUSVString container;
    container.setUSVString(value);
    return container;
}

ArrayBufferOrArrayBufferViewOrBlobOrUSVString::ArrayBufferOrArrayBufferViewOrBlobOrUSVString(const ArrayBufferOrArrayBufferViewOrBlobOrUSVString&) = default;
ArrayBufferOrArrayBufferViewOrBlobOrUSVString::~ArrayBufferOrArrayBufferViewOrBlobOrUSVString() = default;
ArrayBufferOrArrayBufferViewOrBlobOrUSVString& ArrayBufferOrArrayBufferViewOrBlobOrUSVString::operator=(const ArrayBufferOrArrayBufferViewOrBlobOrUSVString&) = default;

DEFINE_TRACE(ArrayBufferOrArrayBufferViewOrBlobOrUSVString)
{
    visitor->trace(m_arrayBuffer);
    visitor->trace(m_arrayBufferView);
    visitor->trace(m_blob);
}

void V8ArrayBufferOrArrayBufferViewOrBlobOrUSVString::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, ArrayBufferOrArrayBufferViewOrBlobOrUSVString& impl, UnionTypeConversionMode conversionMode, ExceptionState& exceptionState)
{
    if (v8Value.IsEmpty())
        return;

    if (conversionMode == UnionTypeConversionMode::Nullable && isUndefinedOrNull(v8Value))
        return;

    if (V8Blob::hasInstance(v8Value, isolate)) {
        Blob* cppValue = V8Blob::toImpl(v8::Local<v8::Object>::Cast(v8Value));
        impl.setBlob(cppValue);
        return;
    }

    if (v8Value->IsArrayBuffer()) {
        DOMArrayBuffer* cppValue = V8ArrayBuffer::toImpl(v8::Local<v8::Object>::Cast(v8Value));
        impl.setArrayBuffer(cppValue);
        return;
    }

    if (v8Value->IsArrayBufferView()) {
        DOMArrayBufferView* cppValue = V8ArrayBufferView::toImpl(v8::Local<v8::Object>::Cast(v8Value));
        impl.setArrayBufferView(cppValue);
        return;
    }

    {
        V8StringResource<> cppValue = toUSVString(isolate, v8Value, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setUSVString(cppValue);
        return;
    }
}

v8::Local<v8::Value> ToV8(const ArrayBufferOrArrayBufferViewOrBlobOrUSVString& impl, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    switch (impl.m_type) {
    case ArrayBufferOrArrayBufferViewOrBlobOrUSVString::SpecificTypeNone:
        return v8::Null(isolate);
    case ArrayBufferOrArrayBufferViewOrBlobOrUSVString::SpecificTypeArrayBuffer:
        return ToV8(impl.getAsArrayBuffer(), creationContext, isolate);
    case ArrayBufferOrArrayBufferViewOrBlobOrUSVString::SpecificTypeArrayBufferView:
        return ToV8(impl.getAsArrayBufferView(), creationContext, isolate);
    case ArrayBufferOrArrayBufferViewOrBlobOrUSVString::SpecificTypeBlob:
        return ToV8(impl.getAsBlob(), creationContext, isolate);
    case ArrayBufferOrArrayBufferViewOrBlobOrUSVString::SpecificTypeUSVString:
        return v8String(isolate, impl.getAsUSVString());
    default:
        NOTREACHED();
    }
    return v8::Local<v8::Value>();
}

ArrayBufferOrArrayBufferViewOrBlobOrUSVString NativeValueTraits<ArrayBufferOrArrayBufferViewOrBlobOrUSVString>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    ArrayBufferOrArrayBufferViewOrBlobOrUSVString impl;
    V8ArrayBufferOrArrayBufferViewOrBlobOrUSVString::toImpl(isolate, value, impl, UnionTypeConversionMode::NotNullable, exceptionState);
    return impl;
}

} // namespace blink
