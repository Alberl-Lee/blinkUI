// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "PaymentCurrencyAmount.h"

namespace blink {

PaymentCurrencyAmount::PaymentCurrencyAmount()
{
    setCurrencySystem(String("urn:iso:std:iso:4217"));
}

PaymentCurrencyAmount::~PaymentCurrencyAmount() { }

PaymentCurrencyAmount::PaymentCurrencyAmount(const PaymentCurrencyAmount&) = default;

PaymentCurrencyAmount& PaymentCurrencyAmount::operator=(const PaymentCurrencyAmount&) = default;

bool PaymentCurrencyAmount::hasCurrency() const
{
    return !m_currency.isNull();
}
String PaymentCurrencyAmount::currency() const
{
    return m_currency;
}
void PaymentCurrencyAmount::setCurrency(String value)
{
    m_currency = value;
}
bool PaymentCurrencyAmount::hasCurrencySystem() const
{
    return !m_currencySystem.isNull();
}
String PaymentCurrencyAmount::currencySystem() const
{
    return m_currencySystem;
}
void PaymentCurrencyAmount::setCurrencySystem(String value)
{
    m_currencySystem = value;
}
bool PaymentCurrencyAmount::hasValue() const
{
    return !m_value.isNull();
}
String PaymentCurrencyAmount::value() const
{
    return m_value;
}
void PaymentCurrencyAmount::setValue(String value)
{
    m_value = value;
}

DEFINE_TRACE(PaymentCurrencyAmount)
{
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
