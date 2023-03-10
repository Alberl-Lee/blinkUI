// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_v8.cpp.tmpl

// clang-format on
#include "V8EventModifierInit.h"

#include "bindings/core/v8/ExceptionState.h"
#include "bindings/core/v8/V8UIEventInit.h"

namespace blink {

void V8EventModifierInit::toImpl(v8::Isolate* isolate, v8::Local<v8::Value> v8Value, EventModifierInit& impl, ExceptionState& exceptionState)
{
    if (isUndefinedOrNull(v8Value)) {
        return;
    }
    if (!v8Value->IsObject()) {
        exceptionState.throwTypeError("cannot convert to dictionary.");
        return;
    }

    V8UIEventInit::toImpl(isolate, v8Value, impl, exceptionState);
    if (exceptionState.hadException())
        return;

    v8::TryCatch block(isolate);
    v8::Local<v8::Object> v8Object;
    if (!v8Call(v8Value->ToObject(isolate->GetCurrentContext()), v8Object, block)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    v8::Local<v8::Value> altKeyValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "altKey")).ToLocal(&altKeyValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (altKeyValue.IsEmpty() || altKeyValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool altKey = toBoolean(isolate, altKeyValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setAltKey(altKey);
    }

    v8::Local<v8::Value> ctrlKeyValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "ctrlKey")).ToLocal(&ctrlKeyValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (ctrlKeyValue.IsEmpty() || ctrlKeyValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool ctrlKey = toBoolean(isolate, ctrlKeyValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setCtrlKey(ctrlKey);
    }

    v8::Local<v8::Value> metaKeyValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "metaKey")).ToLocal(&metaKeyValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (metaKeyValue.IsEmpty() || metaKeyValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool metaKey = toBoolean(isolate, metaKeyValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setMetaKey(metaKey);
    }

    v8::Local<v8::Value> modifierAltGraphValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "modifierAltGraph")).ToLocal(&modifierAltGraphValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (modifierAltGraphValue.IsEmpty() || modifierAltGraphValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool modifierAltGraph = toBoolean(isolate, modifierAltGraphValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setModifierAltGraph(modifierAltGraph);
    }

    v8::Local<v8::Value> modifierCapsLockValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "modifierCapsLock")).ToLocal(&modifierCapsLockValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (modifierCapsLockValue.IsEmpty() || modifierCapsLockValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool modifierCapsLock = toBoolean(isolate, modifierCapsLockValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setModifierCapsLock(modifierCapsLock);
    }

    v8::Local<v8::Value> modifierFnValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "modifierFn")).ToLocal(&modifierFnValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (modifierFnValue.IsEmpty() || modifierFnValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool modifierFn = toBoolean(isolate, modifierFnValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setModifierFn(modifierFn);
    }

    v8::Local<v8::Value> modifierNumLockValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "modifierNumLock")).ToLocal(&modifierNumLockValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (modifierNumLockValue.IsEmpty() || modifierNumLockValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool modifierNumLock = toBoolean(isolate, modifierNumLockValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setModifierNumLock(modifierNumLock);
    }

    v8::Local<v8::Value> modifierScrollLockValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "modifierScrollLock")).ToLocal(&modifierScrollLockValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (modifierScrollLockValue.IsEmpty() || modifierScrollLockValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool modifierScrollLock = toBoolean(isolate, modifierScrollLockValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setModifierScrollLock(modifierScrollLock);
    }

    v8::Local<v8::Value> modifierSymbolValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "modifierSymbol")).ToLocal(&modifierSymbolValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (modifierSymbolValue.IsEmpty() || modifierSymbolValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool modifierSymbol = toBoolean(isolate, modifierSymbolValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setModifierSymbol(modifierSymbol);
    }

    v8::Local<v8::Value> shiftKeyValue;
    if (!v8Object->Get(isolate->GetCurrentContext(), v8String(isolate, "shiftKey")).ToLocal(&shiftKeyValue)) {
        exceptionState.rethrowV8Exception(block.Exception());
        return;
    }
    if (shiftKeyValue.IsEmpty() || shiftKeyValue->IsUndefined()) {
        // Do nothing.
    } else {
        bool shiftKey = toBoolean(isolate, shiftKeyValue, exceptionState);
        if (exceptionState.hadException())
            return;
        impl.setShiftKey(shiftKey);
    }
}

v8::Local<v8::Value> EventModifierInit::toV8Impl(v8::Local<v8::Object> creationContext, v8::Isolate* isolate) const
{
    v8::Local<v8::Object> v8Object = v8::Object::New(isolate);
    if (!toV8EventModifierInit(*this, v8Object, creationContext, isolate))
        return v8::Undefined(isolate);
    return v8Object;
}

bool toV8EventModifierInit(const EventModifierInit& impl, v8::Local<v8::Object> dictionary, v8::Local<v8::Object> creationContext, v8::Isolate* isolate)
{
    if (!toV8UIEventInit(impl, dictionary, creationContext, isolate))
        return false;

    if (impl.hasAltKey()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "altKey"), v8Boolean(impl.altKey(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "altKey"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasCtrlKey()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "ctrlKey"), v8Boolean(impl.ctrlKey(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "ctrlKey"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasMetaKey()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "metaKey"), v8Boolean(impl.metaKey(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "metaKey"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasModifierAltGraph()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierAltGraph"), v8Boolean(impl.modifierAltGraph(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierAltGraph"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasModifierCapsLock()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierCapsLock"), v8Boolean(impl.modifierCapsLock(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierCapsLock"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasModifierFn()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierFn"), v8Boolean(impl.modifierFn(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierFn"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasModifierNumLock()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierNumLock"), v8Boolean(impl.modifierNumLock(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierNumLock"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasModifierScrollLock()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierScrollLock"), v8Boolean(impl.modifierScrollLock(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierScrollLock"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasModifierSymbol()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierSymbol"), v8Boolean(impl.modifierSymbol(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "modifierSymbol"), v8Boolean(false, isolate))))
            return false;
    }

    if (impl.hasShiftKey()) {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "shiftKey"), v8Boolean(impl.shiftKey(), isolate))))
            return false;
    } else {
        if (!v8CallBoolean(dictionary->CreateDataProperty(isolate->GetCurrentContext(), v8String(isolate, "shiftKey"), v8Boolean(false, isolate))))
            return false;
    }

    return true;
}

EventModifierInit NativeValueTraits<EventModifierInit>::nativeValue(v8::Isolate* isolate, v8::Local<v8::Value> value, ExceptionState& exceptionState)
{
    EventModifierInit impl;
    V8EventModifierInit::toImpl(isolate, value, impl, exceptionState);
    return impl;
}

} // namespace blink
