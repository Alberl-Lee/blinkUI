// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file has been auto-generated by code_generator_v8.py.
// DO NOT MODIFY!

// This file has been generated from the Jinja2 template in
// third_party/WebKit/Source/bindings/templates/dictionary_impl.h.tmpl

// clang-format on
#ifndef RTCConfiguration_h
#define RTCConfiguration_h

#include "bindings/core/v8/IDLDictionaryBase.h"
#include "modules/ModulesExport.h"
#include "modules/peerconnection/RTCIceServer.h"
#include "platform/heap/Handle.h"
#include "wtf/Vector.h"
#include "wtf/text/WTFString.h"

namespace blink {

class RTCCertificate;

class MODULES_EXPORT RTCConfiguration : public IDLDictionaryBase {
    DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();

public:
    RTCConfiguration();
    virtual ~RTCConfiguration();
    RTCConfiguration(const RTCConfiguration&);
    RTCConfiguration& operator=(const RTCConfiguration&);

    bool hasBundlePolicy() const;
    String bundlePolicy() const;
    void setBundlePolicy(String);

    bool hasCertificates() const;
    const HeapVector<Member<RTCCertificate>>& certificates() const;
    void setCertificates(const HeapVector<Member<RTCCertificate>>&);

    bool hasIceServers() const;
    const HeapVector<RTCIceServer>& iceServers() const;
    void setIceServers(const HeapVector<RTCIceServer>&);

    bool hasIceTransportPolicy() const;
    String iceTransportPolicy() const;
    void setIceTransportPolicy(String);

    bool hasIceTransports() const;
    String iceTransports() const;
    void setIceTransports(String);

    bool hasRtcpMuxPolicy() const;
    String rtcpMuxPolicy() const;
    void setRtcpMuxPolicy(String);

    v8::Local<v8::Value> toV8Impl(v8::Local<v8::Object>, v8::Isolate*) const override;
    DECLARE_VIRTUAL_TRACE();

private:
    String m_bundlePolicy;
    bool m_hasCertificates = false;
    HeapVector<Member<RTCCertificate>> m_certificates;
    bool m_hasIceServers = false;
    HeapVector<RTCIceServer> m_iceServers;
    String m_iceTransportPolicy;
    String m_iceTransports;
    String m_rtcpMuxPolicy;

    friend class V8RTCConfiguration;
};

} // namespace blink

#endif // RTCConfiguration_h
