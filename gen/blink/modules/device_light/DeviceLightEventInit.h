// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.h.tmpl

// clang-format on
#ifndef DeviceLightEventInit_h
#define DeviceLightEventInit_h

#include "core/events/EventInit.h"
#include "modules/ModulesExport.h"
#include "platform/heap/Handle.h"

namespace blink {

class MODULES_EXPORT DeviceLightEventInit : public EventInit {
    DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();

public:
    DeviceLightEventInit();
    virtual ~DeviceLightEventInit();
    DeviceLightEventInit(const DeviceLightEventInit&);
    DeviceLightEventInit& operator=(const DeviceLightEventInit&);

    bool hasValue() const;
    double value() const;
    void setValue(double);

    v8::Local<v8::Value> toV8Impl(v8::Local<v8::Object>, v8::Isolate*) const override;
    DECLARE_VIRTUAL_TRACE();

private:
    bool m_hasValue = false;
    double m_value;

    friend class V8DeviceLightEventInit;
};

} // namespace blink

#endif // DeviceLightEventInit_h
