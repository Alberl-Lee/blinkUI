/*
 * Copyright (C) 2012 Apple Inc. All rights reserved.
 * Copyright (C) 2014 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef LayoutGeometryMapStep_h
#define LayoutGeometryMapStep_h

#include "platform/geometry/LayoutSize.h"
#include "platform/transforms/TransformationMatrix.h"
#include "wtf/Allocator.h"
#include <memory>

namespace blink {

class LayoutObject;

enum GeometryInfoFlag {
    AccumulatingTransform = 1 << 0,
    IsNonUniform = 1
        << 1, // Mapping depends on the input point, e.g. because of CSS columns.
    IsFixedPosition = 1 << 2,
    ContainsFixedPosition = 1 << 3,
};
typedef unsigned GeometryInfoFlags;

// Stores data about how to map from one layoutObject to its container.
struct LayoutGeometryMapStep {
    DISALLOW_NEW_EXCEPT_PLACEMENT_NEW();
    LayoutGeometryMapStep(const LayoutGeometryMapStep& o)
        : m_layoutObject(o.m_layoutObject)
        , m_offset(o.m_offset)
        , m_offsetForFixedPosition(o.m_offsetForFixedPosition)
        , m_offsetForStickyPosition(o.m_offsetForStickyPosition)
        , m_flags(o.m_flags)
    {
        ASSERT(!o.m_transform);
    }
    LayoutGeometryMapStep(const LayoutObject* layoutObject,
        GeometryInfoFlags flags)
        : m_layoutObject(layoutObject)
        , m_flags(flags)
    {
    }
    const LayoutObject* m_layoutObject;
    LayoutSize m_offset;
    std::unique_ptr<TransformationMatrix>
        m_transform; // Includes offset if non-null.
    // If m_offsetForFixedPosition could only apply to the fixed position steps,
    // we may be able to merge with m_offsetForStickyPosition and simplify
    // mapping.
    LayoutSize m_offsetForFixedPosition;
    LayoutSize m_offsetForStickyPosition;
    GeometryInfoFlags m_flags;
};

} // namespace blink

WTF_ALLOW_MOVE_INIT_AND_COMPARE_WITH_MEM_FUNCTIONS(
    blink::LayoutGeometryMapStep);

#endif // LayoutGeometryMapStep_h
