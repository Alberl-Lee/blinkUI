/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */
#include "PathOpsTestCommon.h"
#include "SkPathOpsCubic.h"
#include "SkPathOpsLine.h"
#include "SkPathOpsQuad.h"
#include "SkPathOpsRect.h"
#include "Test.h"

static const SkDQuad quadTests[] = {
    { { { 1, 1 }, { 2, 1 }, { 0, 2 } } },
    { { { 0, 0 }, { 1, 1 }, { 3, 1 } } },
    { { { 2, 0 }, { 1, 1 }, { 2, 2 } } },
    { { { 4, 0 }, { 0, 1 }, { 4, 2 } } },
    { { { 0, 0 }, { 0, 1 }, { 1, 1 } } },
};

static const SkDCubic cubicTests[] = {
    { { { 2, 0 }, { 3, 1 }, { 2, 2 }, { 1, 1 } } },
    { { { 3, 1 }, { 2, 2 }, { 1, 1 }, { 2, 0 } } },
    { { { 3, 0 }, { 2, 1 }, { 3, 2 }, { 1, 1 } } },
};

static const size_t quadTests_count = SK_ARRAY_COUNT(quadTests);
static const size_t cubicTests_count = SK_ARRAY_COUNT(cubicTests);

static void setRawBounds(const SkDQuad& quad, SkDRect* rect)
{
    rect->set(quad[0]);
    rect->add(quad[1]);
    rect->add(quad[2]);
}

static void setRawBounds(const SkDCubic& cubic, SkDRect* rect)
{
    rect->set(cubic[0]);
    rect->add(cubic[1]);
    rect->add(cubic[2]);
    rect->add(cubic[3]);
}

DEF_TEST(PathOpsDRect, reporter)
{
    size_t index;
    SkDRect rect, rect2;
    for (index = 0; index < quadTests_count; ++index) {
        const SkDQuad& quad = quadTests[index];
        SkASSERT(ValidQuad(quad));
        setRawBounds(quad, &rect);
        rect2.setBounds(quad);
        REPORTER_ASSERT(reporter, rect.intersects(rect2));
        // FIXME: add a recursive box subdivision method to verify that tight bounds is correct
        SkDPoint leftTop = { rect2.fLeft, rect2.fTop };
        REPORTER_ASSERT(reporter, rect.contains(leftTop));
        SkDPoint rightBottom = { rect2.fRight, rect2.fBottom };
        REPORTER_ASSERT(reporter, rect.contains(rightBottom));
    }
    for (index = 0; index < cubicTests_count; ++index) {
        const SkDCubic& cubic = cubicTests[index];
        SkASSERT(ValidCubic(cubic));
        setRawBounds(cubic, &rect);
        rect2.setBounds(cubic);
        REPORTER_ASSERT(reporter, rect.intersects(rect2));
        // FIXME: add a recursive box subdivision method to verify that tight bounds is correct
        SkDPoint leftTop = { rect2.fLeft, rect2.fTop };
        REPORTER_ASSERT(reporter, rect.contains(leftTop));
        SkDPoint rightBottom = { rect2.fRight, rect2.fBottom };
        REPORTER_ASSERT(reporter, rect.contains(rightBottom));
    }
}
