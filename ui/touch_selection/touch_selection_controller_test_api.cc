// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/touch_selection/touch_selection_controller_test_api.h"

namespace ui {

TouchSelectionControllerTestApi::TouchSelectionControllerTestApi(
    TouchSelectionController* controller)
    : controller_(controller)
{
}

TouchSelectionControllerTestApi::~TouchSelectionControllerTestApi() { }

bool TouchSelectionControllerTestApi::GetStartVisible() const
{
    return controller_->GetStartVisible();
}

bool TouchSelectionControllerTestApi::GetEndVisible() const
{
    return controller_->GetEndVisible();
}

TouchHandleOrientation
TouchSelectionControllerTestApi::GetStartHandleOrientation() const
{
    if (controller_->active_status_ != TouchSelectionController::SELECTION_ACTIVE)
        return TouchHandleOrientation::UNDEFINED;
    return controller_->start_selection_handle_->orientation();
}

TouchHandleOrientation
TouchSelectionControllerTestApi::GetEndHandleOrientation() const
{
    if (controller_->active_status_ != TouchSelectionController::SELECTION_ACTIVE)
        return TouchHandleOrientation::UNDEFINED;
    return controller_->end_selection_handle_->orientation();
}

} // namespace ui
