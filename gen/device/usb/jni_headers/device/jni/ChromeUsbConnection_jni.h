// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This file is autogenerated by
//     base/android/jni_generator/jni_generator.py
// For
//     org/chromium/device/usb/ChromeUsbConnection

#ifndef org_chromium_device_usb_ChromeUsbConnection_JNI
#define org_chromium_device_usb_ChromeUsbConnection_JNI

#include <jni.h>

#include "../../../../../../../../base/android/jni_generator/jni_generator_helper.h"

#include "base/android/jni_int_wrapper.h"

// Step 1: forward declarations.
namespace {
const char kChromeUsbConnectionClassPath[] = "org/chromium/device/usb/ChromeUsbConnection";
// Leaking this jclass as we cannot use LazyInstance from some threads.
base::subtle::AtomicWord g_ChromeUsbConnection_clazz __attribute__((unused)) = 0;
#define ChromeUsbConnection_clazz(env) base::android::LazyGetClass(env, kChromeUsbConnectionClassPath, &g_ChromeUsbConnection_clazz)

} // namespace

namespace device {

// Step 2: method stubs.

static base::subtle::AtomicWord g_ChromeUsbConnection_create = 0;
static base::android::ScopedJavaLocalRef<jobject>
Java_ChromeUsbConnection_create(JNIEnv* env, const base::android::JavaRefOrBare<jobject>& connection)
{
    CHECK_CLAZZ(env, ChromeUsbConnection_clazz(env),
        ChromeUsbConnection_clazz(env), NULL);
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_STATIC>(
        env, ChromeUsbConnection_clazz(env),
        "create",
        "("
        "Landroid/hardware/usb/UsbDeviceConnection;"
        ")"
        "Lorg/chromium/device/usb/ChromeUsbConnection;",
        &g_ChromeUsbConnection_create);

    jobject ret = env->CallStaticObjectMethod(ChromeUsbConnection_clazz(env),
        method_id, connection.obj());
    jni_generator::CheckException(env);
    return base::android::ScopedJavaLocalRef<jobject>(env, ret);
}

static base::subtle::AtomicWord g_ChromeUsbConnection_getFileDescriptor = 0;
static jint Java_ChromeUsbConnection_getFileDescriptor(JNIEnv* env, const base::android::JavaRefOrBare<jobject>& obj)
{
    CHECK_CLAZZ(env, obj.obj(),
        ChromeUsbConnection_clazz(env), 0);
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_INSTANCE>(
        env, ChromeUsbConnection_clazz(env),
        "getFileDescriptor",
        "("
        ")"
        "I",
        &g_ChromeUsbConnection_getFileDescriptor);

    jint ret = env->CallIntMethod(obj.obj(),
        method_id);
    jni_generator::CheckException(env);
    return ret;
}

static base::subtle::AtomicWord g_ChromeUsbConnection_close = 0;
static void Java_ChromeUsbConnection_close(JNIEnv* env, const base::android::JavaRefOrBare<jobject>& obj)
{
    CHECK_CLAZZ(env, obj.obj(),
        ChromeUsbConnection_clazz(env));
    jmethodID method_id = base::android::MethodID::LazyGet<
        base::android::MethodID::TYPE_INSTANCE>(
        env, ChromeUsbConnection_clazz(env),
        "close",
        "("
        ")"
        "V",
        &g_ChromeUsbConnection_close);

    env->CallVoidMethod(obj.obj(),
        method_id);
    jni_generator::CheckException(env);
}

// Step 3: RegisterNatives.

} // namespace device

#endif // org_chromium_device_usb_ChromeUsbConnection_JNI
