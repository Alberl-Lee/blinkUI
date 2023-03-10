// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "FetchEventInit.h"

#include "modules/fetch/Request.h"

namespace blink {

FetchEventInit::FetchEventInit()
{
    setIsReload(false);
}

FetchEventInit::~FetchEventInit() { }

FetchEventInit::FetchEventInit(const FetchEventInit&) = default;

FetchEventInit& FetchEventInit::operator=(const FetchEventInit&) = default;

bool FetchEventInit::hasClientId() const
{
    return !m_clientId.isNull();
}
String FetchEventInit::clientId() const
{
    return m_clientId;
}
void FetchEventInit::setClientId(String value)
{
    m_clientId = value;
}
void FetchEventInit::setClientIdToNull()
{
    m_clientId = String();
}
bool FetchEventInit::hasIsReload() const
{
    return m_hasIsReload;
}
bool FetchEventInit::isReload() const
{
    DCHECK(m_hasIsReload);
    return m_isReload;
}
void FetchEventInit::setIsReload(bool value)
{
    m_isReload = value;
    m_hasIsReload = true;
}
bool FetchEventInit::hasRequest() const
{
    return m_request;
}
Request* FetchEventInit::request() const
{
    return m_request;
}
void FetchEventInit::setRequest(Request* value)
{
    m_request = value;
}

DEFINE_TRACE(FetchEventInit)
{
    visitor->trace(m_request);
    ExtendableEventInit::trace(visitor);
}

} // namespace blink
