// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_NATIVE_THEME_NATIVE_THEME_ANDROID_H_
#define UI_NATIVE_THEME_NATIVE_THEME_ANDROID_H_

#include "base/macros.h"
#include "ui/native_theme/native_theme_base.h"

namespace ui {

// Android implementation of native theme support.
class NativeThemeAndroid : public NativeThemeBase {
public:
    static NativeThemeAndroid* instance();

    // NativeThemeBase:
    gfx::Size GetPartSize(Part part,
        State state,
        const ExtraParams& extra) const override;
    SkColor GetSystemColor(ColorId color_id) const override;

protected:
    // NativeThemeBase:
    void AdjustCheckboxRadioRectForPadding(SkRect* rect) const override;

private:
    NativeThemeAndroid();
    ~NativeThemeAndroid() override;

    DISALLOW_COPY_AND_ASSIGN(NativeThemeAndroid);
};

} // namespace ui

#endif // UI_NATIVE_THEME_NATIVE_THEME_ANDROID_H_
