// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BoxDecorationData_h
#define BoxDecorationData_h

#include "core/layout/BackgroundBleedAvoidance.h"
#include "platform/graphics/Color.h"

namespace blink {

class LayoutBox;

// Information extracted from ComputedStyle for box painting.
struct BoxDecorationData {
    STACK_ALLOCATED();

public:
    BoxDecorationData(const LayoutBox&);

    Color backgroundColor;
    BackgroundBleedAvoidance bleedAvoidance;
    bool hasBackground;
    bool hasBorderDecoration;
    bool hasAppearance;

private:
    BackgroundBleedAvoidance determineBackgroundBleedAvoidance(const LayoutBox&);
};

} // namespace blink

#endif
