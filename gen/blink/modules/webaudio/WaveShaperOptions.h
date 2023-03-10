// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.h.tmpl

// clang-format on
#ifndef WaveShaperOptions_h
#define WaveShaperOptions_h

#include "modules/ModulesExport.h"
#include "modules/webaudio/AudioNodeOptions.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace blink {

class MODULES_EXPORT WaveShaperOptions : public AudioNodeOptions {
    DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();

public:
    WaveShaperOptions();
    virtual ~WaveShaperOptions();
    WaveShaperOptions(const WaveShaperOptions&);
    WaveShaperOptions& operator=(const WaveShaperOptions&);

    bool hasCurve() const;
    const Vector<float>& curve() const;
    void setCurve(const Vector<float>&);

    bool hasOversample() const;
    String oversample() const;
    void setOversample(String);

    v8::Local<v8::Value> toV8Impl(v8::Local<v8::Object>, v8::Isolate*) const override;
    DECLARE_VIRTUAL_TRACE();

private:
    bool m_hasCurve = false;
    Vector<float> m_curve;
    String m_oversample;

    friend class V8WaveShaperOptions;
};

} // namespace blink

#endif // WaveShaperOptions_h
