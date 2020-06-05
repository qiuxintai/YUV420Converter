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

#include "convert_utils.h"
#include "logger.h"

/*
 * This function come from:
 * https://github.com/tensorflow/tensorflow/blob/master/tensorflow/examples/android/jni/yuv2rgb.cc
 */
static inline int YUV2RGBA(int nY, int nU, int nV) {
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
static inline void rgbaIntToBytes(int rgba, unsigned char *b) {
    b[0] = (unsigned char) ((rgba >> 16) & 0xff);  //R
    b[1] = (unsigned char) ((rgba >> 8) & 0xff);   //G
    b[2] = (unsigned char) (rgba & 0xff);          //B
    b[3] = (unsigned char) ((rgba >> 24) & 0xff);  //A
}

void YUV420PToRGBAByte(unsigned char *yuv420p, unsigned char *rgba, int width,
                       int height, int yRowStride, int uvRowStride, int uvPixelStride,
                       int format) {
    if (format == YUV420P_I420 || format == YUV420P_YV12) {
        unsigned char *pRGBA = rgba;
        unsigned char *pY = yuv420p;
        unsigned char *pU;
        unsigned char *pV;
        if (format == YUV420P_I420) {
            pU = yuv420p + width * height;
            pV = yuv420p + width * height / 4 * 5;
        } else {
            pU = yuv420p + width * height / 4 * 5;
            pV = yuv420p + width * height;
        }
        for (int y = 0; y < height; y++) {
            const int uvRowStart = uvRowStride * (y >> 1);
            for (int x = 0; x < width; x++) {
                const int uvRowOffset = (x >> 1) * uvPixelStride;
                rgbaIntToBytes(YUV2RGBA(pY[yRowStride * y + x],
                                        pU[uvRowStart + uvRowOffset],
                                        pV[uvRowStart + uvRowOffset]),
                               pRGBA);
                pRGBA += 4;
            }
        }
    }
}

void YUV420PToRGBAInt(unsigned char *yuv420p, int *rgba, int width,
                      int height, int yRowStride, int uvRowStride, int uvPixelStride,
                      int format) {
    if (format == YUV420P_I420 || format == YUV420P_YV12) {
        unsigned char *pY = yuv420p;
        unsigned char *pU;
        unsigned char *pV;
        int rgbaIndex = 0;
        if (format == YUV420P_I420) {
            pU = yuv420p + width * height;
            pV = yuv420p + width * height / 4 * 5;
        } else {
            pU = yuv420p + width * height / 4 * 5;
            pV = yuv420p + width * height;
        }
        for (int y = 0; y < height; y++) {
            const int uvRowStart = uvRowStride * (y >> 1);
            for (int x = 0; x < width; x++) {
                const int uvRowOffset = (x >> 1) * uvPixelStride;
                rgba[rgbaIndex++] = YUV2RGBA(pY[yRowStride * y + x],
                                             pU[uvRowStart + uvRowOffset],
                                             pV[uvRowStart + uvRowOffset]);
            }
        }
    }
}

void YUV420SPToRGBAByte(unsigned char *yuv420sp, unsigned char *rgba, int width, int height,
                        int format) {
    if (format == YUV420SP_NV12 || format == YUV420SP_NV21) {
        unsigned char *pRGBA = rgba;
        unsigned char *pY = yuv420sp;
        unsigned char *pUV = yuv420sp + width * height;
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
    }
}

void YUV420SPToRGBAInt(unsigned char *yuv420sp, int *rgba, int width, int height,
                       int format) {
    if (format == YUV420SP_NV12 || format == YUV420SP_NV21) {
        unsigned char *pY = yuv420sp;
        unsigned char *pUV = yuv420sp + width * height;
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
                rgba[rgbaIndex++] = YUV2RGBA(*pY++, pUV[uOffset], pUV[vOffset]);
            }
        }
    }
}
