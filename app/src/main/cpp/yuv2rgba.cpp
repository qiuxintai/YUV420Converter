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

#include <android/log.h>

#define TAG "YUV420Converter"
#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)

const int K_MAX_CHANNEL_VALUE = 262143;
const int YUV420P_I420 = 1;
const int YUV420P_YV12 = 2;
const int YUV420SP_NV12 = 3;
const int YUV420SP_NV21 = 4;

/*
 * This function come from:
 * https://github.com/tensorflow/tensorflow/blob/master/tensorflow/examples/android/jni/yuv2rgb.cc
 */
static inline jint YUV2RGBA(int nY, int nU, int nV) {
    nY -= 16;
    nU -= 128;
    nV -= 128;
    if (nY < 0) nY = 0;

    // This is the floating point equivalent. We do the conversion in integer
    // because some Android devices do not have floating point in hardware.
    // nR = (int)(1.164 * nY + 2.018 * nU);
    // nG = (int)(1.164 * nY - 0.813 * nV - 0.391 * nU);
    // nB = (int)(1.164 * nY + 1.596 * nV);

    int nR = 1192 * nY + 1634 * nV;
    int nG = 1192 * nY - 833 * nV - 400 * nU;
    int nB = 1192 * nY + 2066 * nU;

    nR = nR > K_MAX_CHANNEL_VALUE ? K_MAX_CHANNEL_VALUE : (nR < 0 ? 0 : nR);
    nG = nG > K_MAX_CHANNEL_VALUE ? K_MAX_CHANNEL_VALUE : (nG < 0 ? 0 : nG);
    nB = nB > K_MAX_CHANNEL_VALUE ? K_MAX_CHANNEL_VALUE : (nB < 0 ? 0 : nB);

    nR = (nR >> 10) & 0xff;
    nG = (nG >> 10) & 0xff;
    nB = (nB >> 10) & 0xff;
    return 0xff000000 | (nR << 16) | (nG << 8) | nB;
}

/*
 * int  order: ARGB
 * byte order: RGBA
 */
static inline void rgbaIntToBytes(int rgba, uint8_t *b) {
    b[0] = (uint8_t) ((rgba >> 16) & 0xff);  //R
    b[1] = (uint8_t) ((rgba >> 8) & 0xff);   //G
    b[2] = (uint8_t) (rgba & 0xff);          //B
    b[3] = (uint8_t) ((rgba >> 24) & 0xff);  //A
}

void YUV420PToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420p, jbyteArray rgba, jint width,
                       jint height, jint yRowStride, jint uvRowStride, jint uvPixelStride,
                       jint format) {
    if (format == YUV420P_I420 || format == YUV420P_YV12) {
        jbyte *_yuv420p = env->GetByteArrayElements(yuv420p, nullptr);
        jbyte *_rgba = env->GetByteArrayElements(rgba, nullptr);

        uint8_t *pRGBA = (uint8_t *) _rgba;
        uint8_t *pY = (uint8_t *) _yuv420p;
        uint8_t *pU;
        uint8_t *pV;
        if (format == YUV420P_I420) {
            pU = (uint8_t *) _yuv420p + width * height;
            pV = (uint8_t *) _yuv420p + width * height / 4 * 5;
        } else {
            pU = (uint8_t *) _yuv420p + width * height / 4 * 5;
            pV = (uint8_t *) _yuv420p + width * height;
        }
        for (int y = 0; y < height; y++) {
            const int uvRowStart = uvRowStride * (y >> 1);
            for (int x = 0; x < width; x++) {
                const int uvRowOffset = (x >> 1) * uvPixelStride;
                rgbaIntToBytes(YUV2RGBA(//*pY++,
                                        pY[yRowStride * y + x],
                                        pU[uvRowStart + uvRowOffset],
                                        pV[uvRowStart + uvRowOffset]), pRGBA);
                pRGBA += 4;
            }
        }

        env->ReleaseByteArrayElements(yuv420p, _yuv420p, JNI_ABORT);
        env->ReleaseByteArrayElements(rgba, _rgba, 0);
    }
}

void YUV420PToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420p, jintArray rgba, jint width,
                      jint height, jint yRowStride, jint uvRowStride, jint uvPixelStride,
                      jint format) {
    if (format == YUV420P_I420 || format == YUV420P_YV12) {
        jbyte *_yuv420p = env->GetByteArrayElements(yuv420p, NULL);
        jint *_rgba = env->GetIntArrayElements(rgba, NULL);

        uint8_t *pY = (uint8_t *) _yuv420p;
        uint8_t *pU;
        uint8_t *pV;
        int rgbaIndex = 0;
        if (format == YUV420P_I420) {
            pU = (uint8_t *) _yuv420p + width * height;
            pV = (uint8_t *) _yuv420p + width * height / 4 * 5;
        } else {
            pU = (uint8_t *) _yuv420p + width * height / 4 * 5;
            pV = (uint8_t *) _yuv420p + width * height;
        }
        for (int y = 0; y < height; y++) {
            const int uvRowStart = uvRowStride * (y >> 1);
            for (int x = 0; x < width; x++) {
                const int uvRowOffset = (x >> 1) * uvPixelStride;
                _rgba[rgbaIndex++] = YUV2RGBA(//*pY++,
                                              pY[yRowStride * y + x],
                                              pU[uvRowStart + uvRowOffset],
                                              pV[uvRowStart + uvRowOffset]);
            }
        }

        env->ReleaseByteArrayElements(yuv420p, _yuv420p, JNI_ABORT);
        env->ReleaseIntArrayElements(rgba, _rgba, 0);
    }
}

void YUV420SPToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420sp, jbyteArray rgba,
                        jint width, jint height, jint format) {
    if (format == YUV420SP_NV12 || format == YUV420SP_NV21) {
        jbyte *_yuv420sp = env->GetByteArrayElements(yuv420sp, NULL);
        jbyte *_rgba = env->GetByteArrayElements(rgba, NULL);

        uint8_t *pRGBA = (uint8_t *) _rgba;
        uint8_t *pY = (uint8_t *) _yuv420sp;
        uint8_t *pUV = (uint8_t *) (_yuv420sp + width * height);
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int uvOffset = (y >> 1) * width + 2 * (x >> 1);
                int uOffset;
                int vOffset;
                if (format == YUV420SP_NV12) {
                    uOffset = uvOffset;
                    vOffset = uvOffset + 1;
                } else {
                    uOffset = uvOffset + 1;
                    vOffset = uvOffset;
                }
                rgbaIntToBytes(YUV2RGBA(*pY++, pUV[uOffset], pUV[vOffset]), pRGBA);
                pRGBA += 4;
            }
        }

        env->ReleaseByteArrayElements(yuv420sp, _yuv420sp, JNI_ABORT);
        env->ReleaseByteArrayElements(rgba, _rgba, 0);
    }
}

void YUV420SPToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420sp, jintArray rgba,
                       jint width, jint height, jint format) {
    if (format == YUV420SP_NV12 || format == YUV420SP_NV21) {
        jbyte *_yuv420sp = env->GetByteArrayElements(yuv420sp, NULL);
        jint *_rgba = env->GetIntArrayElements(rgba, NULL);

        uint8_t *pY = (uint8_t *) _yuv420sp;
        uint8_t *pUV = (uint8_t *) (_yuv420sp + width * height);
        int rgbaIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int uvOffset = (y >> 1) * width + 2 * (x >> 1);
                int uOffset;
                int vOffset;
                if (format == YUV420SP_NV12) {
                    uOffset = uvOffset;
                    vOffset = uvOffset + 1;
                } else {
                    uOffset = uvOffset + 1;
                    vOffset = uvOffset;
                }
                _rgba[rgbaIndex++] = YUV2RGBA(*pY++, pUV[uOffset], pUV[vOffset]);
            }
        }

        env->ReleaseByteArrayElements(yuv420sp, _yuv420sp, JNI_ABORT);
        env->ReleaseIntArrayElements(rgba, _rgba, 0);
    }
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_I420ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                 jint width, jint height,
                                                 jint yRowStride, jint uvRowStride,
                                                 jint uvPixelStride, jbyteArray rgba) {
    YUV420PToRGBAByte(env, clazz, yuv420p, rgba, width, height, yRowStride, uvRowStride,
                      uvPixelStride, YUV420P_I420);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_I420ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                jint width, jint height,
                                                jint yRowStride, jint uvRowStride,
                                                jint uvPixelStride, jintArray rgba) {
    YUV420PToRGBAInt(env, clazz, yuv420p, rgba, width, height, yRowStride, uvRowStride,
                     uvPixelStride, YUV420P_I420);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_YV12ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                 jint width, jint height,
                                                 jint yRowStride, jint uvRowStride,
                                                 jint uvPixelStride, jbyteArray rgba) {
    YUV420PToRGBAByte(env, clazz, yuv420p, rgba, width, height, yRowStride, uvRowStride,
                      uvPixelStride, YUV420P_YV12);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_YV12ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420p,
                                                jint width, jint height,
                                                jint yRowStride, jint uvRowStride,
                                                jint uvPixelStride, jintArray rgba) {
    YUV420PToRGBAInt(env, clazz, yuv420p, rgba, width, height, yRowStride, uvRowStride,
                     uvPixelStride, YUV420P_YV12);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_NV12ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                 jint width, jint height,
                                                 jbyteArray rgba) {
    YUV420SPToRGBAByte(env, clazz, yuv420sp, rgba, width, height, YUV420SP_NV12);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_NV12ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                jint width, jint height,
                                                jintArray rgba) {
    YUV420SPToRGBAInt(env, clazz, yuv420sp, rgba, width, height, YUV420SP_NV12);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_NV21ToRGBAByte(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                 jint width, jint height,
                                                 jbyteArray rgba) {
    YUV420SPToRGBAByte(env, clazz, yuv420sp, rgba, width, height, YUV420SP_NV21);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_NV21ToRGBAInt(JNIEnv *env, jclass clazz, jbyteArray yuv420sp,
                                                jint width, jint height, jintArray rgba) {
    YUV420SPToRGBAInt(env, clazz, yuv420sp, rgba, width, height, YUV420SP_NV21);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_rotateByte(JNIEnv *env, jclass clazz, jbyteArray src,
                                             jbyteArray dst, jint width, jint height, jint bpp,
                                             jfloat degree) {
    LOGD("[rotateByte] width:%d, height:%d, bpp:%d, degree:%f, length:%d",
         width, height, bpp, degree, width * height * bpp);
    uint8_t *_src = (uint8_t *) env->GetByteArrayElements(src, nullptr);
    uint8_t *_dst = (uint8_t *) env->GetByteArrayElements(dst, nullptr);

    int dstIndex = 0;
    int srcIndex = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (degree == 90.0f) {
                //(y, x) -> (x, height - y - 1)
                //y * width + x, -> x* height + height - y - 1
                dstIndex = (x * height + height - y - 1) * bpp;
            } else if (degree == 180.0f) {
                //(y, x) -> (height - y - 1, width - x - 1)
                //y * width + x, -> (height - y - 1) * width + width - x - 1
                dstIndex = ((height - y - 1) * width + width - x - 1) * bpp;
            } else if (degree == 270.0f) {
                //(y, x) -> (width - x - 1, y)
                //y * width + x, -> (width - x - 1) * height + y
                dstIndex = ((width - x - 1) * height + y) * bpp;
            } else {
                dstIndex = (y * width + x) * bpp;
            }
            srcIndex = (y * width + x) * bpp;
            for (int i = 0; i < bpp; i++) {
                _dst[dstIndex + i] = _src[srcIndex + i];
            }
        }
    }
    env->ReleaseByteArrayElements(src, (jbyte *) _src, JNI_ABORT);
    env->ReleaseByteArrayElements(dst, (jbyte *) _dst, 0);
}

extern "C"
JNIEXPORT void JNICALL
Java_com_qxt_yuv420_YUV2RGBAUtils_rotateInt(JNIEnv *env, jclass clazz, jintArray src,
                                            jintArray dst, jint width, jint height,
                                            jfloat degree) {
    LOGD("[rotateInt] width:%d, height:%d, degree:%f, length:%d",
            width, height, degree, width * height);
    int32_t *_src = env->GetIntArrayElements(src, nullptr);
    int32_t *_dst = env->GetIntArrayElements(dst, nullptr);

    int dstIndex = 0;
    int srcIndex = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (degree == 90.0f) {
                //(y, x) -> (x, height - y - 1)
                //y * width + x, -> x* height + height - y - 1
                dstIndex = x * height + height - y - 1;
            } else if (degree == 180.0f) {
                //(y, x) -> (height - y - 1, width - x - 1)
                //y * width + x, -> (height - y - 1) * width + width - x - 1
                dstIndex = (height - y - 1) * width + width - x - 1;
            } else if (degree == 270.0f) {
                //(y, x) -> (width - x - 1, y)
                //y * width + x, -> (width - x - 1) * height + y
                dstIndex = (width - x - 1) * height + y;
            } else {
                dstIndex = y * width + x;
            }
            srcIndex = y * width + x;
            _dst[dstIndex] = _src[srcIndex];
        }
    }
    env->ReleaseIntArrayElements(src, _src, JNI_ABORT);
    env->ReleaseIntArrayElements(dst, _dst, 0);
}