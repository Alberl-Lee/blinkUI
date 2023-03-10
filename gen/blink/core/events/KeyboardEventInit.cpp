// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "KeyboardEventInit.h"

namespace blink {

KeyboardEventInit::KeyboardEventInit()
{
    setCode(String(""));
    setIsComposing(false);
    setKey(String(""));
    setLocation(0u);
    setRepeat(false);
}

KeyboardEventInit::~KeyboardEventInit() { }

KeyboardEventInit::KeyboardEventInit(const KeyboardEventInit&) = default;

KeyboardEventInit& KeyboardEventInit::operator=(const KeyboardEventInit&) = default;

bool KeyboardEventInit::hasCode() const
{
    return !m_code.isNull();
}
String KeyboardEventInit::code() const
{
    return m_code;
}
void KeyboardEventInit::setCode(String value)
{
    m_code = value;
}
bool KeyboardEventInit::hasIsComposing() const
{
    return m_hasIsComposing;
}
bool KeyboardEventInit::isComposing() const
{
    DCHECK(m_hasIsComposing);
    return m_isComposing;
}
void KeyboardEventInit::setIsComposing(bool value)
{
    m_isComposing = value;
    m_hasIsComposing = true;
}
bool KeyboardEventInit::hasKey() const
{
    return !m_key.isNull();
}
String KeyboardEventInit::key() const
{
    return m_key;
}
void KeyboardEventInit::setKey(String value)
{
    m_key = value;
}
bool KeyboardEventInit::hasLocation() const
{
    return m_hasLocation;
}
unsigned KeyboardEventInit::location() const
{
    DCHECK(m_hasLocation);
    return m_location;
}
void KeyboardEventInit::setLocation(unsigned value)
{
    m_location = value;
    m_hasLocation = true;
}
bool KeyboardEventInit::hasRepeat() const
{
    return m_hasRepeat;
}
bool KeyboardEventInit::repeat() const
{
    DCHECK(m_hasRepeat);
    return m_repeat;
}
void KeyboardEventInit::setRepeat(bool value)
{
    m_repeat = value;
    m_hasRepeat = true;
}

DEFINE_TRACE(KeyboardEventInit)
{
    EventModifierInit::trace(visitor);
}

} // namespace blink
