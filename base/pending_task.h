// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PENDING_TASK_H_
#define BASE_PENDING_TASK_H_

#include <queue>

#include "base/base_export.h"
#include "base/callback.h"
#include "base/location.h"
#include "base/time/time.h"
#include "base/tracking_info.h"

namespace base {

// Contains data about a pending task. Stored in TaskQueue and DelayedTaskQueue
// for use by classes that queue and execute tasks.
struct BASE_EXPORT PendingTask : public TrackingInfo {
    PendingTask(const tracked_objects::Location& posted_from, /*OnceClosure*/ Closure task);
    PendingTask(const tracked_objects::Location& posted_from,
        /*OnceClosure*/ Closure task,
        TimeTicks delayed_run_time,
        bool nestable);
    PendingTask(PendingTask&& other);
    PendingTask(const PendingTask& other);
    ~PendingTask();

    PendingTask& operator=(PendingTask&& other);

    // Used to support sorting.
    bool operator<(const PendingTask& other) const;

    // The task to run.
    /*OnceClosure*/ Closure task;

    // The site this PendingTask was posted from.
    tracked_objects::Location posted_from;

    // Secondary sort key for run time.
    int sequence_num;

    // OK to dispatch from a nested loop.
    bool nestable;

    // Needs high resolution timers.
    bool is_high_res;
};

using TaskQueue = std::queue<PendingTask>;

// PendingTasks are sorted by their |delayed_run_time| property.
using DelayedTaskQueue = std::priority_queue<base::PendingTask>;

} // namespace base

#endif // BASE_PENDING_TASK_H_
