// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.cpp.tmpl

// clang-format on
#include "OfflineAudioCompletionEventInit.h"

#include "modules/webaudio/AudioBuffer.h"

namespace blink {

OfflineAudioCompletionEventInit::OfflineAudioCompletionEventInit()
{
}

OfflineAudioCompletionEventInit::~OfflineAudioCompletionEventInit() { }

OfflineAudioCompletionEventInit::OfflineAudioCompletionEventInit(const OfflineAudioCompletionEventInit&) = default;

OfflineAudioCompletionEventInit& OfflineAudioCompletionEventInit::operator=(const OfflineAudioCompletionEventInit&) = default;

bool OfflineAudioCompletionEventInit::hasRenderedBuffer() const
{
    return m_renderedBuffer;
}
AudioBuffer* OfflineAudioCompletionEventInit::renderedBuffer() const
{
    return m_renderedBuffer;
}
void OfflineAudioCompletionEventInit::setRenderedBuffer(AudioBuffer* value)
{
    m_renderedBuffer = value;
}

DEFINE_TRACE(OfflineAudioCompletionEventInit)
{
    visitor->trace(m_renderedBuffer);
    EventInit::trace(visitor);
}

} // namespace blink
