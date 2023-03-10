/*
 * Copyright 2012 Google Inc.
 *
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */

#include "PathOpsThreadedCommon.h"
#include "PathOpsExtendedTest.h"
#include "SkTaskGroup.h"

PathOpsThreadedTestRunner::~PathOpsThreadedTestRunner()
{
    for (int index = 0; index < fRunnables.count(); index++) {
        delete fRunnables[index];
    }
}

void PathOpsThreadedTestRunner::render()
{
    SkTaskGroup().batch(fRunnables.count(), [&](int i) {
        (*fRunnables[i])();
    });
}
