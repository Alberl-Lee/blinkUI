// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//
//    org/chromium/components/navigation_interception/InterceptNavigationDelegate

#ifndef org_chromium_components_navigation_interception_InterceptNavigationDelegate_JNI
#define org_chromium_components_navigation_interception_InterceptNavigationDelegate_JNI

#include <jni.h>

#include "../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

#include "base/android/jni_int_wrapper.h"

// Step 1: forward declarations.
namespace {
const char kInterceptNavigationDelegateClassPath[] = "org/chromium/components/navigation_interception/InterceptNavigationDelegate";
// Leaking this jclass as we cannot use LazyInstance from some threads.
base::subtle::AtomicWord g_InterceptNavigationDelegate_clazz
    __attribute__((unused))
    = 0;
#define InterceptNavigationDelegate_clazz(env) base::android::LazyGetClass(env, kInterceptNavigationDelegateClassPath, &g_InterceptNavigationDelegate_clazz)

} // namespace

// Step 2: method stubs.

static base::subtle::AtomicWord
    g_InterceptNavigationDelegate_shouldIgnoreNavigation
    = 0;
static jboolean Java_InterceptNavigationDelegate_shouldIgnoreNavigation(JNIEnv*
                                                                            env,
    const base::android::JavaRefOrBare<jobject>& obj, const base::android::JavaRefOrBare<jobject>& navigationParams)
{
    CHECK_CLAZZ(env, obj.obj(),
        InterceptNavigationDelegate_clazz(env), false);
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_INSTANCE>(
        env, InterceptNavigationDelegate_clazz(env),
        "shouldIgnoreNavigation",
        "("
        "Lorg/chromium/components/navigation_interception/NavigationParams;"
        ")"
        "Z",
        &g_InterceptNavigationDelegate_shouldIgnoreNavigation);

    jboolean ret = env->CallBooleanMethod(obj.obj(),
        method_id, navigationParams.obj());
    jni_generator::CheckException(env);
    return ret;
}

// Step 3: RegisterNatives.

#endif // org_chromium_components_navigation_interception_InterceptNavigationDelegate_JNI
