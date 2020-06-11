#include <jni.h>
#include <string>
#include "opencv_utils.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_I420ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    opencvI420ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_YV12ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    opencvYV12ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_NV12ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    opencvNV12ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_NV21ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    opencvNV21ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_rotateRGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                          jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    opencvRotateRGB(reinterpret_cast<unsigned char *>(_src), width, height, degree);
    env->ReleaseByteArrayElements(src, _src, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_rotateRGBA(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    opencvRotateRGBA(reinterpret_cast<unsigned char *>(_src), width, height, degree);
    env->ReleaseByteArrayElements(src, _src, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_OpencvUtils_rotateYUV420P(JNIEnv *env, jclass clazz, jbyteArray src,
                                              jint width, jint height, jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    opencvRotateYUV420P(reinterpret_cast<unsigned char *>(_src), width, height, degree);
    env->ReleaseByteArrayElements(src, _src, 0);
}