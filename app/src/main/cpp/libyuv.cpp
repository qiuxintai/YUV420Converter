#include <jni.h>
#include <string>
#include "libyuv_utils.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_I420ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvI420ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_YV12ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvYV12ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_NV12ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvNV12ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_NV21ToRGBA(JNIEnv *env, jclass clazz,
                                           jbyteArray src, jbyteArray dst,
                                           jint width, jint height) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvNV21ToRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst), width, height);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}
extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_rotateRGB(JNIEnv *env, jclass clazz, jbyteArray src,
                                          jbyteArray dst, jint width, jint height,
                                          jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvRotateRGB(reinterpret_cast<unsigned char *>(_src),
                    reinterpret_cast<unsigned char *>(_dst),
                    width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_rotateRGBA(JNIEnv *env, jclass clazz, jbyteArray src,
                                           jbyteArray dst, jint width, jint height,
                                           jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvRotateRGBA(reinterpret_cast<unsigned char *>(_src),
                     reinterpret_cast<unsigned char *>(_dst),
                     width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_rotateYUV420P(JNIEnv *env, jclass clazz, jbyteArray src,
                                              jbyteArray dst, jint width, jint height,
                                              jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvRotateYUV420P(reinterpret_cast<unsigned char *>(_src),
                        reinterpret_cast<unsigned char *>(_dst),
                        width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_LibyuvUtils_rotateYUV420SP(JNIEnv *env, jclass clazz, jbyteArray src,
                                               jbyteArray dst, jint width, jint height,
                                               jfloat degree) {
    jbyte *_src = env->GetByteArrayElements(src, nullptr);
    jbyte *_dst = env->GetByteArrayElements(dst, nullptr);
    libyuvRotateYUV420SP(reinterpret_cast<unsigned char *>(_src),
                         reinterpret_cast<unsigned char *>(_dst),
                         width, height, degree);
    env->ReleaseByteArrayElements(src, _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, _dst, 0);
}

