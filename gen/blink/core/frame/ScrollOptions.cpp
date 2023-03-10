// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "ScrollOptions.h"

namespace blink {

ScrollOptions::ScrollOptions()
{
    setBehavior(String("auto"));
}

ScrollOptions::~ScrollOptions() { }

ScrollOptions::ScrollOptions(const ScrollOptions&) = default;

ScrollOptions& ScrollOptions::operator=(const ScrollOptions&) = default;

bool ScrollOptions::hasBehavior() const
{
    return !m_behavior.isNull();
}
String ScrollOptions::behavior() const
{
    return m_behavior;
}
void ScrollOptions::setBehavior(String value)
{
    m_behavior = value;
}

DEFINE_TRACE(ScrollOptions)
{
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
