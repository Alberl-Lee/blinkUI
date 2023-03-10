// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "PerformanceObserverInit.h"

namespace blink {

PerformanceObserverInit::PerformanceObserverInit()
{
}

PerformanceObserverInit::~PerformanceObserverInit() { }

PerformanceObserverInit::PerformanceObserverInit(const PerformanceObserverInit&) = default;

PerformanceObserverInit& PerformanceObserverInit::operator=(const PerformanceObserverInit&) = default;

bool PerformanceObserverInit::hasEntryTypes() const
{
    return m_hasEntryTypes;
}
const Vector<String>& PerformanceObserverInit::entryTypes() const
{
    DCHECK(m_hasEntryTypes);
    return m_entryTypes;
}
void PerformanceObserverInit::setEntryTypes(const Vector<String>& value)
{
    m_entryTypes = value;
    m_hasEntryTypes = true;
}

DEFINE_TRACE(PerformanceObserverInit)
{
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
