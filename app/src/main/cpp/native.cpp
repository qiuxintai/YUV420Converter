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

#include "convert_utils.h"
#include "rotate_utils.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_I420ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                     jint width, jint height,
                                                     jint yRowStride, jint uvRowStride,
                                                     jint uvPixelStride, jbyteArray rgba) {
    jbyte *_yuv420p = env->GetByteArrayElements(yuv420p, nullptr);
    jbyte *_rgba = env->GetByteArrayElements(rgba, nullptr);
    LOGD("I420ToRGBAByte---start");
    YUV420PToRGBAByte(reinterpret_cast<unsigned char *>(_yuv420p),
                      reinterpret_cast<unsigned char *>(_rgba),
                      width, height, yRowStride, uvRowStride, uvPixelStride, YUV420P_I420);
    LOGD("I420ToRGBAByte---end");
    env->ReleaseByteArrayElements(yuv420p, _yuv420p, JNI_ABORT);
    env->ReleaseByteArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_I420ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                    jint width, jint height,
                                                    jint yRowStride, jint uvRowStride,
                                                    jint uvPixelStride, jintArray rgba) {
    jbyte *_yuv420p = env->GetByteArrayElements(yuv420p, NULL);
    jint *_rgba = env->GetIntArrayElements(rgba, NULL);
    YUV420PToRGBAInt(reinterpret_cast<unsigned char *>(_yuv420p), _rgba, width, height, yRowStride,
                     uvRowStride, uvPixelStride, YUV420P_I420);
    env->ReleaseByteArrayElements(yuv420p, _yuv420p, JNI_ABORT);
    env->ReleaseIntArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_YV12ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                     jint width, jint height,
                                                     jint yRowStride, jint uvRowStride,
                                                     jint uvPixelStride, jbyteArray rgba) {
    jbyte *_yuv420p = env->GetByteArrayElements(yuv420p, nullptr);
    jbyte *_rgba = env->GetByteArrayElements(rgba, nullptr);
    YUV420PToRGBAByte(reinterpret_cast<unsigned char *>(_yuv420p),
                      reinterpret_cast<unsigned char *>(_rgba),
                      width, height, yRowStride, uvRowStride, uvPixelStride, YUV420P_YV12);
    env->ReleaseByteArrayElements(yuv420p, _yuv420p, JNI_ABORT);
    env->ReleaseByteArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_YV12ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                    jint width, jint height,
                                                    jint yRowStride, jint uvRowStride,
                                                    jint uvPixelStride, jintArray rgba) {
    jbyte *_yuv420p = env->GetByteArrayElements(yuv420p, NULL);
    jint *_rgba = env->GetIntArrayElements(rgba, NULL);
    YUV420PToRGBAInt(reinterpret_cast<unsigned char *>(_yuv420p),
                     _rgba, width, height, yRowStride, uvRowStride, uvPixelStride, YUV420P_YV12);
    env->ReleaseByteArrayElements(yuv420p, _yuv420p, JNI_ABORT);
    env->ReleaseIntArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_NV12ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                     jint width, jint height,
                                                     jbyteArray rgba) {
    LOGD("NV12ToRGBAByte---start");
    jbyte *_yuv420sp = env->GetByteArrayElements(yuv420sp, NULL);
    jbyte *_rgba = env->GetByteArrayElements(rgba, NULL);
    YUV420SPToRGBAByte(reinterpret_cast<unsigned char *>(_yuv420sp),
                       reinterpret_cast<unsigned char *>(_rgba), width, height, YUV420SP_NV12);
    env->ReleaseByteArrayElements(yuv420sp, _yuv420sp, JNI_ABORT);
    env->ReleaseByteArrayElements(rgba, _rgba, 0);
    LOGD("NV12ToRGBAByte---end");
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_NV12ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                    jint width, jint height,
                                                    jintArray rgba) {
    jbyte *_yuv420sp = env->GetByteArrayElements(yuv420sp, NULL);
    jint *_rgba = env->GetIntArrayElements(rgba, NULL);
    YUV420SPToRGBAInt(reinterpret_cast<unsigned char *>(_yuv420sp),
                      _rgba, width, height, YUV420SP_NV12);
    env->ReleaseByteArrayElements(yuv420sp, _yuv420sp, JNI_ABORT);
    env->ReleaseIntArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_NV21ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                     jint width, jint height,
                                                     jbyteArray rgba) {
    jbyte *_yuv420sp = env->GetByteArrayElements(yuv420sp, NULL);
    jbyte *_rgba = env->GetByteArrayElements(rgba, NULL);
    YUV420SPToRGBAByte(reinterpret_cast<unsigned char *>(_yuv420sp),
                       reinterpret_cast<unsigned char *>(_rgba), width, height, YUV420SP_NV21);
    env->ReleaseByteArrayElements(yuv420sp, _yuv420sp, JNI_ABORT);
    env->ReleaseByteArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_Yuv420ToRgbaUtils_NV21ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                    jint width, jint height, jintArray rgba) {
    jbyte *_yuv420sp = env->GetByteArrayElements(yuv420sp, NULL);
    jint *_rgba = env->GetIntArrayElements(rgba, NULL);
    YUV420SPToRGBAInt(reinterpret_cast<unsigned char *>(_yuv420sp),
                      _rgba, width, height, YUV420SP_NV21);
    env->ReleaseByteArrayElements(yuv420sp, _yuv420sp, JNI_ABORT);
    env->ReleaseIntArrayElements(rgba, _rgba, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_RotateUtils_rotateRGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                          jbyteArray dst, jint width, jint height,
                                          jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    rotateRGB(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
              width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_RotateUtils_rotateRGBA(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height,
                                           jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    LOGD("rotateRGBA---start");
    rotateRGBA(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
               width, height, degree);
    LOGD("rotateRGBA---end");
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_RotateUtils_rotateRGBAInt(JNIEnv *env, jclass clazz, jintArray src,
                                              jintArray dst, jint width, jint height,
                                              jfloat degree) {
    int *_src = env->GetIntArrayElements(src, nullptr);
    int *_dst = env->GetIntArrayElements(dst, nullptr);
    LOGD("rotateRGBAInt---start");
    rotateRGBAInt(_src, _dst, width, height, degree);
    LOGD("rotateRGBAInt---end");
    env->ReleaseIntArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_RotateUtils_rotateYUV420P(JNIEnv *env, jclass clazz, jbyteArray src,
                                              jbyteArray dst, jint width, jint height,
                                              jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    LOGD("rotateYUV420P---start");
    rotateYUV420P(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
                  width, height, degree);
    LOGD("rotateYUV420P---end");
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_RotateUtils_rotateYUV420SP(JNIEnv *env, jclass clazz, jbyteArray src,
                                               jbyteArray dst, jint width, jint height,
                                               jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    LOGD("rotateYUV420SP---start");
    rotateYUV420SP(reinterpret_cast<unsigned char *>(_src), reinterpret_cast<unsigned char *>(_dst),
                   width, height, degree);
    LOGD("rotateYUV420SP---end");
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}