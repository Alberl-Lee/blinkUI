// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/gfx/font_render_params.h"

#include "base/logging.h"
#include "base/macros.h"

namespace gfx {

namespace {

    // Returns the system's default settings.
    FontRenderParams LoadDefaults()
    {
        FontRenderParams params;
        params.antialiasing = true;
        params.autohinter = true;
        params.use_bitmaps = true;
        params.subpixel_rendering = FontRenderParams::SUBPIXEL_RENDERING_NONE;

        // Use subpixel text positioning to keep consistent character spacing when
        // the page is scaled by a fractional factor.
        params.subpixel_positioning = true;
        // Slight hinting renders much better than normal hinting on Android.
        params.hinting = FontRenderParams::HINTING_SLIGHT;

        return params;
    }

} // namespace

FontRenderParams GetFontRenderParams(const FontRenderParamsQuery& query,
    std::string* family_out)
{
    if (family_out)
        NOTIMPLEMENTED();
    // Customized font rendering settings are not supported, only defaults.
    CR_DEFINE_STATIC_LOCAL(const gfx::FontRenderParams, params, (LoadDefaults()));
    return params;
}

} // namespace gfx
