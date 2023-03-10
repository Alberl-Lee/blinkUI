// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "PaymentAppOption.h"

namespace blink {

PaymentAppOption::PaymentAppOption()
{
}

PaymentAppOption::~PaymentAppOption() { }

PaymentAppOption::PaymentAppOption(const PaymentAppOption&) = default;

PaymentAppOption& PaymentAppOption::operator=(const PaymentAppOption&) = default;

bool PaymentAppOption::hasEnabledMethods() const
{
    return m_hasEnabledMethods;
}
const Vector<String>& PaymentAppOption::enabledMethods() const
{
    DCHECK(m_hasEnabledMethods);
    return m_enabledMethods;
}
void PaymentAppOption::setEnabledMethods(const Vector<String>& value)
{
    m_enabledMethods = value;
    m_hasEnabledMethods = true;
}
bool PaymentAppOption::hasIcon() const
{
    return !m_icon.isNull();
}
String PaymentAppOption::icon() const
{
    return m_icon;
}
void PaymentAppOption::setIcon(String value)
{
    m_icon = value;
}
void PaymentAppOption::setIconToNull()
{
    m_icon = String();
}
bool PaymentAppOption::hasId() const
{
    return !m_id.isNull();
}
String PaymentAppOption::id() const
{
    return m_id;
}
void PaymentAppOption::setId(String value)
{
    m_id = value;
}
bool PaymentAppOption::hasName() const
{
    return !m_name.isNull();
}
String PaymentAppOption::name() const
{
    return m_name;
}
void PaymentAppOption::setName(String value)
{
    m_name = value;
}

DEFINE_TRACE(PaymentAppOption)
{
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
