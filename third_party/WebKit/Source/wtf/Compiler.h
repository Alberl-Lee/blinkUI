/*
 * Copyright (C) 2011, 2012 Apple Inc. All rights reserved.
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
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WTF_Compiler_h
#define WTF_Compiler_h

#include "base/compiler_specific.h"

/* COMPILER() - the compiler being used to build the project */
#define COMPILER(WTF_FEATURE) \
    (defined WTF_COMPILER_##WTF_FEATURE && WTF_COMPILER_##WTF_FEATURE)

/* ==== COMPILER() - the compiler being used to build the project ==== */

/* COMPILER(CLANG) - Clang  */
#if defined(__clang__)
#define WTF_COMPILER_CLANG 1
#endif

/* COMPILER(MSVC) - Microsoft Visual C++ (and Clang when compiling for Windows).
 */
#if defined(_MSC_VER)
#define WTF_COMPILER_MSVC 1
#endif

/* COMPILER(GCC) - GNU Compiler Collection (and Clang when compiling for
 * platforms other than Windows). */
#if defined(__GNUC__)
#define WTF_COMPILER_GCC 1
#define GCC_VERSION \
    (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#define GCC_VERSION_AT_LEAST(major, minor, patch) \
    (GCC_VERSION >= (major * 10000 + minor * 100 + patch))
#else
/* Define this for !GCC compilers, just so we can write things like
 * GCC_VERSION_AT_LEAST(4, 1, 0). */
#define GCC_VERSION_AT_LEAST(major, minor, patch) 0
#endif

/* ==== Compiler features ==== */

/* NEVER_INLINE */

// TODO(palmer): Remove this and update callers to use NOINLINE from Chromium
// base. https://bugs.chromium.org/p/chromium/issues/detail?id=632441
#ifndef NEVER_INLINE
#define NEVER_INLINE NOINLINE
#endif

/* OBJC_CLASS */

#ifndef OBJC_CLASS
#ifdef __OBJC__
#define OBJC_CLASS @class
#else
#define OBJC_CLASS class
#endif
#endif

/* WTF_PRETTY_FUNCTION */

#if COMPILER(GCC)
#define WTF_PRETTY_FUNCTION __PRETTY_FUNCTION__
#elif COMPILER(MSVC)
#define WTF_PRETTY_FUNCTION __FUNCSIG__
#else
#define WTF_PRETTY_FUNCTION __func__
#endif

/* NO_SANITIZE_UNRELATED_CAST - Disable runtime checks related to casts between
 * unrelated objects (-fsanitize=cfi-unrelated-cast or -fsanitize=vptr). */

#if COMPILER(CLANG)
#define NO_SANITIZE_UNRELATED_CAST \
    __attribute__((no_sanitize("cfi-unrelated-cast", "vptr")))
#else
#define NO_SANITIZE_UNRELATED_CAST
#endif

#ifndef ALWAYS_INLINE
#define ALWAYS_INLINE inline
#endif

//#define LIKELY
#define ASSERT_WITH_SECURITY_IMPLICATION(x) ASSERT(x)
#define WARN_UNUSED_RETURN

#define DISABLE_CFI_PERF

#endif /* WTF_Compiler_h */
