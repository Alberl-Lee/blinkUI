/*
 * Copyright (C) 2008 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1.  Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 * 2.  Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 * 3.  Neither the name of Apple Computer, Inc. ("Apple") nor the names of
 *     its contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE AND ITS CONTRIBUTORS "AS IS" AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL APPLE OR ITS CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef AXTableCell_h
#define AXTableCell_h

#include "modules/accessibility/AXLayoutObject.h"

namespace blink {

class AXObjectCacheImpl;

class MODULES_EXPORT AXTableCell : public AXLayoutObject {
    WTF_MAKE_NONCOPYABLE(AXTableCell);

protected:
    AXTableCell(LayoutObject*, AXObjectCacheImpl&);

public:
    static AXTableCell* create(LayoutObject*, AXObjectCacheImpl&);
    ~AXTableCell() override;

    bool isTableCell() const final;

    // fills in the start location and row span of cell
    virtual void rowIndexRange(std::pair<unsigned, unsigned>& rowRange);
    // fills in the start location and column span of cell
    virtual void columnIndexRange(std::pair<unsigned, unsigned>& columnRange);
    // In the case of cells that act as row or column headers.
    SortDirection getSortDirection() const final;
    virtual AccessibilityRole scanToDecideHeaderRole();

    unsigned ariaColumnIndex() const;
    unsigned ariaRowIndex() const;
    void setARIAColIndexFromRow(int index) { m_ariaColIndexFromRow = index; }

protected:
    virtual AXObject* parentTable() const;
    AccessibilityRole determineAccessibilityRole() final;

private:
    bool isTableHeaderCell() const;
    bool isRowHeaderCell() const;
    bool isColumnHeaderCell() const;

    bool computeAccessibilityIsIgnored(IgnoredReasons* = nullptr) const final;

    unsigned m_ariaColIndexFromRow;
};

DEFINE_AX_OBJECT_TYPE_CASTS(AXTableCell, isTableCell());

} // namespace blink

#endif // AXTableCell_h
