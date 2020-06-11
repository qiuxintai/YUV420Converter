/*
 * Copyright 2020 Tyler Qiu.
 * YUV420 to RGBA open source project.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>
#include <string>

#include "native_utils.h"

using namespace native_utils;

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_I420ToRGBAByte(JNIEnv *env, jclass clazz,
                                               jbyteArray src, jbyteArray dst,
                                               jint width, jint height, jint yRowStride,
                                               jint uvRowStride, jint uvPixelStride) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    YUV420PToRGBAByte(reinterpret_cast<unsigned char *>(_src),
                      reinterpret_cast<unsigned char *>(_dst),
                      width, height, yRowStride, uvRowStride, uvPixelStride, YUV420P_I420);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_I420ToRGBAInt(JNIEnv *env, jclass clazz,
                                              jbyteArray src, jintArray dst,
                                              jint width, jint height, jint yRowStride,
                                              jint uvRowStride, jint uvPixelStride) {
    jbyte *_src = env->GetByteArrayElements(src, NULL);
    jint *_dst = env->GetIntArrayElements(dst, NULL);
    YUV420PToRGBAInt(reinterpret_cast<unsigned char *>(_src), _dst, width, height, yRowStride,
                     uvRowStride, uvPixelStride, YUV420P_I420);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_YV12ToRGBAByte(JNIEnv *env, jclass clazz,
                                               jbyteArray src, jbyteArray dst,
                                               jint width, jint height, jint yRowStride,
                                               jint uvRowStride, jint uvPixelStride) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    YUV420PToRGBAByte(reinterpret_cast<unsigned char *>(_src),
                      reinterpret_cast<unsigned char *>(_dst),
                      width, height, yRowStride, uvRowStride, uvPixelStride, YUV420P_YV12);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_YV12ToRGBAInt(JNIEnv *env, jclass clazz,
                                              jbyteArray src, jintArray dst,
                                              jint width, jint height, jint yRowStride,
                                              jint uvRowStride, jint uvPixelStride) {
    jbyte *_src = env->GetByteArrayElements(src, NULL);
    jint *_dst = env->GetIntArrayElements(dst, NULL);
    YUV420PToRGBAInt(reinterpret_cast<unsigned char *>(_src),
                     _dst, width, height, yRowStride, uvRowStride, uvPixelStride, YUV420P_YV12);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_NV12ToRGBAByte(JNIEnv *env, jclass clazz,
                                               jbyteArray src, jbyteArray dst,
                                               jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, NULL);
    jbyte *_dst = env->GetByteArrayElements(dst, NULL);
    YUV420SPToRGBAByte(reinterpret_cast<unsigned char *>(_src),
                       reinterpret_cast<unsigned char *>(_dst), width, height, YUV420SP_NV12);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_NV12ToRGBAInt(JNIEnv *env, jclass clazz,
                                              jbyteArray src, jintArray dst,
                                              jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, NULL);
    jint *_dst = env->GetIntArrayElements(dst, NULL);
    YUV420SPToRGBAInt(reinterpret_cast<unsigned char *>(_src), _dst, width, height, YUV420SP_NV12);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_NV21ToRGBAByte(JNIEnv *env, jclass clazz,
                                               jbyteArray src, jbyteArray dst,
                                               jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, NULL);
    jbyte *_dst = env->GetByteArrayElements(dst, NULL);
    YUV420SPToRGBAByte(reinterpret_cast<unsigned char *>(_src),
                       reinterpret_cast<unsigned char *>(_dst), width, height, YUV420SP_NV21);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_NV21ToRGBAInt(JNIEnv *env, jclass clazz,
                                              jbyteArray src, jintArray dst,
                                              jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, NULL);
    jint *_dst = env->GetIntArrayElements(dst, NULL);
    YUV420SPToRGBAInt(reinterpret_cast<unsigned char *>(_src), _dst, width, height, YUV420SP_NV21);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_rotateRGB(JNIEnv *env, jclass clazz,
                                          jbyteArray src, jbyteArray dst,
                                          jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    rotateRGB(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
              width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_rotateRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    rotateRGBA(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
               width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_rotateRGBAInt(JNIEnv *env, jclass clazz,
                                              jintArray src, jintArray dst,
                                              jint width, jint height, jfloat degree) {
    int *_src = env->GetIntArrayElements(src, nullptr);
    int *_dst = env->GetIntArrayElements(dst, nullptr);
    rotateRGBAInt(_src, _dst, width, height, degree);
    env->ReleaseIntArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_rotateYUV420P(JNIEnv *env, jclass clazz,
                                              jbyteArray src, jbyteArray dst,
                                              jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    rotateYUV420P(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
                  width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_NativeUtils_rotateYUV420SP(JNIEnv *env, jclass clazz,
                                               jbyteArray src, jbyteArray dst,
                                               jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    rotateYUV420SP(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
                   width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}