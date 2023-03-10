// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "MediaRecorderOptions.h"

namespace blink {

MediaRecorderOptions::MediaRecorderOptions()
{
}

MediaRecorderOptions::~MediaRecorderOptions() { }

MediaRecorderOptions::MediaRecorderOptions(const MediaRecorderOptions&) = default;

MediaRecorderOptions& MediaRecorderOptions::operator=(const MediaRecorderOptions&) = default;

bool MediaRecorderOptions::hasAudioBitsPerSecond() const
{
    return m_hasAudioBitsPerSecond;
}
unsigned MediaRecorderOptions::audioBitsPerSecond() const
{
    DCHECK(m_hasAudioBitsPerSecond);
    return m_audioBitsPerSecond;
}
void MediaRecorderOptions::setAudioBitsPerSecond(unsigned value)
{
    m_audioBitsPerSecond = value;
    m_hasAudioBitsPerSecond = true;
}
bool MediaRecorderOptions::hasBitsPerSecond() const
{
    return m_hasBitsPerSecond;
}
unsigned MediaRecorderOptions::bitsPerSecond() const
{
    DCHECK(m_hasBitsPerSecond);
    return m_bitsPerSecond;
}
void MediaRecorderOptions::setBitsPerSecond(unsigned value)
{
    m_bitsPerSecond = value;
    m_hasBitsPerSecond = true;
}
bool MediaRecorderOptions::hasMimeType() const
{
    return !m_mimeType.isNull();
}
String MediaRecorderOptions::mimeType() const
{
    return m_mimeType;
}
void MediaRecorderOptions::setMimeType(String value)
{
    m_mimeType = value;
}
bool MediaRecorderOptions::hasVideoBitsPerSecond() const
{
    return m_hasVideoBitsPerSecond;
}
unsigned MediaRecorderOptions::videoBitsPerSecond() const
{
    DCHECK(m_hasVideoBitsPerSecond);
    return m_videoBitsPerSecond;
}
void MediaRecorderOptions::setVideoBitsPerSecond(unsigned value)
{
    m_videoBitsPerSecond = value;
    m_hasVideoBitsPerSecond = true;
}

DEFINE_TRACE(MediaRecorderOptions)
{
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
