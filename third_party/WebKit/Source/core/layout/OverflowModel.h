/*
 * Copyright (C) 2003, 2004, 2005, 2006, 2007, 2008, 2009 Apple Inc. All rights
 * reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 *
 */

#ifndef OverflowModel_h
#define OverflowModel_h

#include "platform/geometry/LayoutRect.h"

namespace blink {

inline void uniteLayoutOverflowRect(LayoutRect& layoutOverflow,
    const LayoutRect& rect)
{
    LayoutUnit maxX = std::max(rect.maxX(), layoutOverflow.maxX());
    LayoutUnit maxY = std::max(rect.maxY(), layoutOverflow.maxY());
    LayoutUnit minX = std::min(rect.x(), layoutOverflow.x());
    LayoutUnit minY = std::min(rect.y(), layoutOverflow.y());
    // In case the width/height is larger than LayoutUnit can represent, fix the
    // right/bottom edge and shift the top/left ones.
    layoutOverflow.setWidth(maxX - minX);
    layoutOverflow.setHeight(maxY - minY);
    layoutOverflow.setX(maxX - layoutOverflow.width());
    layoutOverflow.setY(maxY - layoutOverflow.height());
}

// OverflowModel classes track content that spills out of an object.
// SimpleOverflowModel is used by InlineFlowBox, and BoxOverflowModel is
// used by LayoutBox.
//
// SimpleOverflowModel tracks 2 types of overflows: layout and visual
// overflows. BoxOverflowModel separates visual overflow into self visual
// overflow and contents visual overflow.
//
// All overflows are in the coordinate space of the object (i.e. physical
// coordinates with flipped block-flow direction). See documentation of
// LayoutBoxModelObject and LayoutBox::noOverflowRect() for more details.
//
// The classes model the overflows as rectangles that unite all the sources of
// overflow. This is the natural choice for layout overflow (scrollbars are
// linear in nature, thus are modeled by rectangles in 2D). For visual overflow
// and content visual overflow, this is a first order simplification though as
// they can be thought of as a collection of (potentially overlapping)
// rectangles.
//
// Layout overflow is the overflow that is reachable via scrollbars. It is used
// to size the scrollbar thumb and determine its position, which is determined
// by the maximum layout overflow size.
// Layout overflow cannot occur without an overflow clip as this is the only way
// to get scrollbars. As its name implies, it is a direct consequence of layout.
// Example of layout overflow:
// * in the inline case, a tall image could spill out of a line box.
// * 'height' / 'width' set to a value smaller than the one needed by the
//   descendants.
// Due to how scrollbars work, no overflow in the logical top and logical left
// direction is allowed(see LayoutBox::addLayoutOverflow).
//
// Visual overflow covers all the effects that visually bleed out of the box.
// Its primary use is to determine the area to invalidate.
// Visual overflow includes ('text-shadow' / 'box-shadow'), text stroke,
// 'outline', 'border-image', etc.
//
// An overflow model object is allocated only when some of these fields have
// non-default values in the owning object. Care should be taken to use adder
// functions (addLayoutOverflow, addVisualOverflow, etc.) to keep this
// invariant.

class SimpleOverflowModel {
    WTF_MAKE_NONCOPYABLE(SimpleOverflowModel);
    USING_FAST_MALLOC(SimpleOverflowModel);

public:
    SimpleOverflowModel(const LayoutRect& layoutRect,
        const LayoutRect& visualRect)
        : m_layoutOverflow(layoutRect)
        , m_visualOverflow(visualRect)
    {
    }

    const LayoutRect& layoutOverflowRect() const { return m_layoutOverflow; }
    void setLayoutOverflow(const LayoutRect& rect) { m_layoutOverflow = rect; }
    void addLayoutOverflow(const LayoutRect& rect)
    {
        uniteLayoutOverflowRect(m_layoutOverflow, rect);
    }

    const LayoutRect& visualOverflowRect() const { return m_visualOverflow; }
    void setVisualOverflow(const LayoutRect& rect) { m_visualOverflow = rect; }
    void addVisualOverflow(const LayoutRect& rect)
    {
        m_visualOverflow.unite(rect);
    }

    void move(LayoutUnit dx, LayoutUnit dy)
    {
        m_layoutOverflow.move(dx, dy);
        m_visualOverflow.move(dx, dy);
    }

private:
    LayoutRect m_layoutOverflow;
    LayoutRect m_visualOverflow;
};

// BoxModelOverflow tracks overflows of a LayoutBox. It separates visual
// overflow into self visual overflow and contents visual overflow.
//
// Self visual overflow covers all the effects of the object itself that
// visually bleed out of the box.
//
// Content visual overflow includes anything that would bleed out of the box and
// would be clipped by the overflow clip ('overflow' != visible). This
// corresponds to children that overflows their parent.
// It's important to note that this overflow ignores descendants with
// self-painting layers (see the SELF-PAINTING LAYER section in PaintLayer).
// This is required by the simplification made by this model (single united
// rectangle) to avoid gigantic invalidation. A good example for this is
// positioned objects that can be anywhere on the page and could artificially
// inflate the visual overflow.
// The main use of content visual overflow is to prevent unneeded clipping in
// BoxPainter (see https://crbug.com/238732). Note that the code path for
// self-painting layer is handled by PaintLayerPainter, which relies on
// PaintLayerClipper and thus ignores this optimization.
//
// Visual overflow covers self visual overflow, and if the box doesn't clip
// overflow, also content visual overflow. OverflowModel doesn't keep visual
// overflow, but keeps self visual overflow and contents visual overflow
// separately. The box should use self visual overflow as visual overflow if
// it clips overflow, otherwise union of self visual overflow and contents
// visual overflow.

class BoxOverflowModel {
public:
    BoxOverflowModel(const LayoutRect& layoutRect,
        const LayoutRect& selfVisualOverflowRect)
        : m_layoutOverflow(layoutRect)
        , m_selfVisualOverflow(selfVisualOverflowRect)
    {
    }

    const LayoutRect& layoutOverflowRect() const { return m_layoutOverflow; }
    void setLayoutOverflow(const LayoutRect& rect) { m_layoutOverflow = rect; }
    void addLayoutOverflow(const LayoutRect& rect)
    {
        uniteLayoutOverflowRect(m_layoutOverflow, rect);
    }

    const LayoutRect& selfVisualOverflowRect() const
    {
        return m_selfVisualOverflow;
    }
    void addSelfVisualOverflow(const LayoutRect& rect)
    {
        m_selfVisualOverflow.unite(rect);
    }

    const LayoutRect& contentsVisualOverflowRect() const
    {
        return m_contentsVisualOverflow;
    }
    void addContentsVisualOverflow(const LayoutRect& rect)
    {
        m_contentsVisualOverflow.unite(rect);
    }

    void move(LayoutUnit dx, LayoutUnit dy)
    {
        m_layoutOverflow.move(dx, dy);
        m_selfVisualOverflow.move(dx, dy);
        m_contentsVisualOverflow.move(dx, dy);
    }

    LayoutUnit layoutClientAfterEdge() const { return m_layoutClientAfterEdge; }
    void setLayoutClientAfterEdge(LayoutUnit clientAfterEdge)
    {
        m_layoutClientAfterEdge = clientAfterEdge;
    }

private:
    LayoutRect m_layoutOverflow;
    LayoutRect m_selfVisualOverflow;
    LayoutRect m_contentsVisualOverflow;
    LayoutUnit m_layoutClientAfterEdge;
};

} // namespace blink

#endif // OverflowModel_h
