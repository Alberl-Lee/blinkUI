// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "modules/webaudio/StereoPannerNode.h"
#include "core/testing/DummyPageHolder.h"
#include "modules/webaudio/OfflineAudioContext.h"
#include "testing/gtest/include/gtest/gtest.h"
#include <memory>

namespace blink {

TEST(StereoPannerNodeTest, StereoPannerLifetime)
{
    std::unique_ptr<DummyPageHolder> page = DummyPageHolder::create();
    OfflineAudioContext* context = OfflineAudioContext::create(
        &page->document(), 2, 1, 48000, ASSERT_NO_EXCEPTION);
    StereoPannerNode* node = context->createStereoPanner(ASSERT_NO_EXCEPTION);
    StereoPannerHandler& handler = static_cast<StereoPannerHandler&>(node->handler());
    EXPECT_TRUE(handler.m_stereoPanner);
    BaseAudioContext::AutoLocker locker(context);
    handler.dispose();
    // m_stereoPanner should live after dispose() because an audio thread is
    // using it.
    EXPECT_TRUE(handler.m_stereoPanner);
}

} // namespace blink
