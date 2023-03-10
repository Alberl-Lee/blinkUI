// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "MediaStreamAudioSourceOptions.h"

#include "modules/mediastream/MediaStream.h"

namespace blink {

MediaStreamAudioSourceOptions::MediaStreamAudioSourceOptions()
{
}

MediaStreamAudioSourceOptions::~MediaStreamAudioSourceOptions() { }

MediaStreamAudioSourceOptions::MediaStreamAudioSourceOptions(const MediaStreamAudioSourceOptions&) = default;

MediaStreamAudioSourceOptions& MediaStreamAudioSourceOptions::operator=(const MediaStreamAudioSourceOptions&) = default;

bool MediaStreamAudioSourceOptions::hasMediaStream() const
{
    return m_mediaStream;
}
MediaStream* MediaStreamAudioSourceOptions::mediaStream() const
{
    return m_mediaStream;
}
void MediaStreamAudioSourceOptions::setMediaStream(MediaStream* value)
{
    m_mediaStream = value;
}

DEFINE_TRACE(MediaStreamAudioSourceOptions)
{
    visitor->trace(m_mediaStream);
    IDLDictionaryBase::trace(visitor);
}

} // namespace blink
