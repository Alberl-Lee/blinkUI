// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef StackFrameDepth_h
#define StackFrameDepth_h

#include "platform/PlatformExport.h"
#include "wtf/Allocator.h"
#include "wtf/Assertions.h"
#include <cstddef>
#include <stdint.h>

namespace blink {

// StackFrameDepth keeps track of current call stack frame depth.
// It is specifically used to control stack usage while tracing
// the object graph during a GC.
//
// Use isSafeToRecurse() to determine if it is safe to consume
// more stack by invoking another recursive call.
class PLATFORM_EXPORT StackFrameDepth final {
    DISALLOW_NEW();

public:
    StackFrameDepth()
        : m_stackFrameLimit(kMinimumStackLimit)
    {
    }
    bool isSafeToRecurse()
    {
        // Asssume that the stack grows towards lower addresses, which
        // all the ABIs currently supported do.
        //
        // A unit test checks that the assumption holds for a target
        // (HeapTest.StackGrowthDirection.)
        return currentStackFrame() > m_stackFrameLimit;
    }

    void enableStackLimit();
    void disableStackLimit() { m_stackFrameLimit = kMinimumStackLimit; }

    bool isEnabled() { return m_stackFrameLimit != kMinimumStackLimit; }
    bool isAcceptableStackUse()
    {
#if defined(ADDRESS_SANITIZER)
        // ASan adds extra stack usage leading to too noisy asserts.
        return true;
#else
        return !isEnabled() || isSafeToRecurse();
#endif
    }

#if COMPILER(MSVC)
// Ignore C4172: returning address of local variable or temporary: dummy. This
// warning suppression has to go outside of the function to take effect.
#pragma warning(push)
#pragma warning(disable : 4172)
#endif
    static uintptr_t currentStackFrame(const char* dummy = nullptr)
    {
#if COMPILER(GCC)
        return reinterpret_cast<uintptr_t>(__builtin_frame_address(0));
#elif COMPILER(MSVC)
        return reinterpret_cast<uintptr_t>(&dummy) - sizeof(void*);
#else
#error "Stack frame pointer estimation not supported on this platform."
        return 0;
#endif
    }
#if COMPILER(MSVC)
#pragma warning(pop)
#endif

private:
    // The maximum depth of eager, unrolled trace() calls that is
    // considered safe and allowed for targets with an unknown
    // thread stack size.
    static const int kSafeStackFrameSize = 32 * 1024;

    // The stack pointer is assumed to grow towards lower addresses;
    // |kMinimumStackLimit| then being the limit that a stack
    // pointer will always exceed.
    static const uintptr_t kMinimumStackLimit = ~0ul;

    static uintptr_t getFallbackStackLimit();

    // The (pointer-valued) stack limit.
    uintptr_t m_stackFrameLimit;
};

class StackFrameDepthScope {
    STACK_ALLOCATED();
    WTF_MAKE_NONCOPYABLE(StackFrameDepthScope);

public:
    explicit StackFrameDepthScope(StackFrameDepth* depth)
        : m_depth(depth)
    {
        m_depth->enableStackLimit();
        // Enabled unless under stack pressure.
        DCHECK(m_depth->isSafeToRecurse() || !m_depth->isEnabled());
    }

    ~StackFrameDepthScope() { m_depth->disableStackLimit(); }

private:
    StackFrameDepth* m_depth;
};

} // namespace blink

#endif // StackFrameDepth_h
