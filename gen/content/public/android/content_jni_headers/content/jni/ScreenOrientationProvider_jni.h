// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/content/browser/ScreenOrientationProvider

#ifndef org_chromium_content_browser_ScreenOrientationProvider_JNI
#define org_chromium_content_browser_ScreenOrientationProvider_JNI

#include <jni.h>

#include "../../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

#include "base/android/jni_int_wrapper.h"

// Step 1: forward declarations.
namespace {
const char kScreenOrientationProviderClassPath[] = "org/chromium/content/browser/ScreenOrientationProvider";
// Leaking this jclass as we cannot use LazyInstance from some threads.
base::subtle::AtomicWord g_ScreenOrientationProvider_clazz
    __attribute__((unused))
    = 0;
#define ScreenOrientationProvider_clazz(env) base::android::LazyGetClass(env, kScreenOrientationProviderClassPath, &g_ScreenOrientationProvider_clazz)

} // namespace

namespace content {

// Step 2: method stubs.

static base::subtle::AtomicWord g_ScreenOrientationProvider_lockOrientation = 0;
static void Java_ScreenOrientationProvider_lockOrientation(JNIEnv* env, const base::android::JavaRefOrBare<jobject>& window,
    jbyte webScreenOrientation)
{
    CHECK_CLAZZ(env, ScreenOrientationProvider_clazz(env),
        ScreenOrientationProvider_clazz(env));
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_STATIC>(
        env, ScreenOrientationProvider_clazz(env),
        "lockOrientation",
        "("
        "Lorg/chromium/ui/base/WindowAndroid;"
        "B"
        ")"
        "V",
        &g_ScreenOrientationProvider_lockOrientation);

    env->CallStaticVoidMethod(ScreenOrientationProvider_clazz(env),
        method_id, window.obj(), webScreenOrientation);
    jni_generator::CheckException(env);
}

static base::subtle::AtomicWord g_ScreenOrientationProvider_unlockOrientation = 0;
static void Java_ScreenOrientationProvider_unlockOrientation(JNIEnv* env, const base::android::JavaRefOrBare<jobject>& window)
{
    CHECK_CLAZZ(env, ScreenOrientationProvider_clazz(env),
        ScreenOrientationProvider_clazz(env));
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_STATIC>(
        env, ScreenOrientationProvider_clazz(env),
        "unlockOrientation",
        "("
        "Lorg/chromium/ui/base/WindowAndroid;"
        ")"
        "V",
        &g_ScreenOrientationProvider_unlockOrientation);

    env->CallStaticVoidMethod(ScreenOrientationProvider_clazz(env),
        method_id, window.obj());
    jni_generator::CheckException(env);
}

static base::subtle::AtomicWord
    g_ScreenOrientationProvider_startAccurateListening
    = 0;
static void Java_ScreenOrientationProvider_startAccurateListening(JNIEnv* env)
{
    CHECK_CLAZZ(env, ScreenOrientationProvider_clazz(env),
        ScreenOrientationProvider_clazz(env));
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_STATIC>(
        env, ScreenOrientationProvider_clazz(env),
        "startAccurateListening",
        "("
        ")"
        "V",
        &g_ScreenOrientationProvider_startAccurateListening);

    env->CallStaticVoidMethod(ScreenOrientationProvider_clazz(env),
        method_id);
    jni_generator::CheckException(env);
}

static base::subtle::AtomicWord
    g_ScreenOrientationProvider_stopAccurateListening
    = 0;
static void Java_ScreenOrientationProvider_stopAccurateListening(JNIEnv* env)
{
    CHECK_CLAZZ(env, ScreenOrientationProvider_clazz(env),
        ScreenOrientationProvider_clazz(env));
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_STATIC>(
        env, ScreenOrientationProvider_clazz(env),
        "stopAccurateListening",
        "("
        ")"
        "V",
        &g_ScreenOrientationProvider_stopAccurateListening);

    env->CallStaticVoidMethod(ScreenOrientationProvider_clazz(env),
        method_id);
    jni_generator::CheckException(env);
}

// Step 3: RegisterNatives.

} // namespace content

#endif // org_chromium_content_browser_ScreenOrientationProvider_JNI
