// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_OZONE_DEVICE_EVENT_OBSERVER_H_
#define UI_EVENTS_OZONE_DEVICE_EVENT_OBSERVER_H_

#include "ui/events/ozone/events_ozone_export.h"

namespace ui {

class DeviceEvent;

class EVENTS_OZONE_EXPORT DeviceEventObserver {
public:
    virtual ~DeviceEventObserver() { }

    virtual void OnDeviceEvent(const DeviceEvent& event) = 0;
};

} // namespace ui

#endif // UI_EVENTS_OZONE_DEVICE_EVENT_OBSERVER_H_
