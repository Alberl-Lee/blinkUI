// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "HitRegionOptions.h"

#include "core/dom/Element.h"
#include "modules/canvas2d/Path2D.h"

namespace blink {

HitRegionOptions::HitRegionOptions()
{
    setFillRule(String("nonzero"));
    setId(String(""));
}

HitRegionOptions::~HitRegionOptions() { }

HitRegionOptions::HitRegionOptions(const HitRegionOptions&) = default;

HitRegionOptions& HitRegionOptions::operator=(const HitRegionOptions&) = default;

bool HitRegionOptions::hasControl() const
{
    return m_control;
}
Element* HitRegionOptions::control() const
{
    return m_control;
}
void HitRegionOptions::setControl(Element* value)
{
    m_control = value;
}
void HitRegionOptions::setControlToNull()
{
    m_control = Member<Element>();
}
bool HitRegionOptions::hasFillRule() const
{
    return !m_fillRule.isNull();
}
String HitRegionOptions::fillRule() const
{
    return m_fillRule;
}
void HitRegionOptions::setFillRule(String value)
{
    m_fillRule = value;
}
bool HitRegionOptions::hasId() const
{
    return !m_id.isNull();
}
String HitRegionOptions::id() const
{
    return m_id;
}
void HitRegionOptions::setId(String value)
{
    m_id = value;
}
bool HitRegionOptions::hasPath() const
{
    return m_path;
}
Path2D* HitRegionOptions::path() const
{
    return m_path;
}
void HitRegionOptions::setPath(Path2D* value)
{
    m_path = value;
}
void HitRegionOptions::setPathToNull()
{
    m_path = Member<Path2D>();
}

DEFINE_TRACE(HitRegionOptions)
{
    visitor->trace(m_control);
    visitor->trace(m_path);
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
