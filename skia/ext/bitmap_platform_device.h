// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SKIA_EXT_BITMAP_PLATFORM_DEVICE_H_
#define SKIA_EXT_BITMAP_PLATFORM_DEVICE_H_

// This file provides an easy way to include the appropriate
// BitmapPlatformDevice header file for your platform.

#include <stdint.h>

#if defined(WIN32)
#include "skia/ext/bitmap_platform_device_win.h"
#elif defined(__APPLE__)
#include "skia/ext/bitmap_platform_device_mac.h"
#elif defined(USE_CAIRO)
#include "skia/ext/bitmap_platform_device_cairo.h"
#else
#include "skia/ext/bitmap_platform_device_skia.h"
#endif

#endif // SKIA_EXT_BITMAP_PLATFORM_DEVICE_H_
