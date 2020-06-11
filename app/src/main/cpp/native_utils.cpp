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

#include "native_utils.h"

namespace native_utils {

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

    void YUV420PToRGBAByte(unsigned char *src, unsigned char *dst, int width, int height,
                           int yRowStride, int uvRowStride, int uvPixelStride, int format) {
        if (format == YUV420P_I420 || format == YUV420P_YV12) {
            unsigned char *pRGBA = dst;
            unsigned char *pY = src;
            unsigned char *pU;
            unsigned char *pV;
            if (format == YUV420P_I420) {
                pU = src + width * height;
                pV = src + width * height / 4 * 5;
            } else {
                pU = src + width * height / 4 * 5;
                pV = src + width * height;
            }
            for (int y = 0; y < height; y++) {
                //const int yRowStart = yRowStride * y;
                const int uvRowStart = uvRowStride * (y >> 1);
                for (int x = 0; x < width; x++) {
                    const int uvRowOffset = (x >> 1) * uvPixelStride;
                    rgbaIntToBytes(YUV2RGBA(*pY++,//pY[yRowStart + x],
                                            pU[uvRowStart + uvRowOffset],
                                            pV[uvRowStart + uvRowOffset]),
                                   pRGBA);
                    pRGBA += 4;
                }
            }
        }
    }

    void YUV420PToRGBAInt(unsigned char *src, int *dst, int width, int height,
                          int yRowStride, int uvRowStride, int uvPixelStride, int format) {
        if (format == YUV420P_I420 || format == YUV420P_YV12) {
            unsigned char *pY = src;
            unsigned char *pU;
            unsigned char *pV;
            int rgbaIndex = 0;
            if (format == YUV420P_I420) {
                pU = src + width * height;
                pV = src + width * height / 4 * 5;
            } else {
                pU = src + width * height / 4 * 5;
                pV = src + width * height;
            }
            for (int y = 0; y < height; y++) {
                //const int yRowStart = yRowStride * y;
                const int uvRowStart = uvRowStride * (y >> 1);
                for (int x = 0; x < width; x++) {
                    const int uvRowOffset = (x >> 1) * uvPixelStride;
                    dst[rgbaIndex++] = YUV2RGBA(*pY++,//pY[yRowStart + x],
                                                 pU[uvRowStart + uvRowOffset],
                                                pV[uvRowStart + uvRowOffset]);
                }
            }
        }
    }

    void YUV420SPToRGBAByte(unsigned char *src, unsigned char *dst, int width, int height,
                            int format) {
        if (format == YUV420SP_NV12 || format == YUV420SP_NV21) {
            unsigned char *pRGBA = dst;
            unsigned char *pY = src;
            unsigned char *pUV = src + width * height;
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

    void YUV420SPToRGBAInt(unsigned char *src, int *dst, int width, int height,
                           int format) {
        if (format == YUV420SP_NV12 || format == YUV420SP_NV21) {
            unsigned char *pY = src;
            unsigned char *pUV = src + width * height;
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
                    dst[rgbaIndex++] = YUV2RGBA(*pY++, pUV[uOffset], pUV[vOffset]);
                }
            }
        }
    }

    static inline void
    rotateYUV420P90(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
                    unsigned char *dstY, unsigned char *dstU, unsigned char *dstV,
                    int width, int height) {
        //rotate y
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstIndex = x * height + height - y - 1;
                dstY[dstIndex] = srcY[srcIndex++];
            }
        }

        //rotate uv
        int uvHeight = height / 2;
        int uvWidth = width / 2;
        int dstUVIndex = 0;
        int srcUVIndex = 0;
        for (int y = 0; y < uvHeight; y++) {
            for (int x = 0; x < uvWidth; x++) {
                dstUVIndex = x * uvHeight + uvHeight - y - 1;
                dstU[dstUVIndex] = srcU[srcUVIndex];
                dstV[dstUVIndex] = srcV[srcUVIndex];
                srcUVIndex++;
            }
        }
    }

    static inline void
    rotateYUV420P180(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
                     unsigned char *dstY, unsigned char *dstU, unsigned char *dstV,
                     int width, int height) {
        //rotate y
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstIndex = (height - y - 1) * width + width - x - 1;
                dstY[dstIndex] = srcY[srcIndex++];
            }
        }

        //rotate uv
        int uvHeight = height / 2;
        int uvWidth = width / 2;
        int dstUVIndex = 0;
        int srcUVIndex = 0;
        for (int y = 0; y < uvHeight; y++) {
            for (int x = 0; x < uvWidth; x++) {
                dstUVIndex = (uvHeight - y - 1) * uvWidth + uvWidth - x - 1;
                dstU[dstUVIndex] = srcU[srcUVIndex];
                dstV[dstUVIndex] = srcV[srcUVIndex];
                srcUVIndex++;
            }
        }
    }

    static inline void
    rotateYUV420P270(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
                     unsigned char *dstY, unsigned char *dstU, unsigned char *dstV,
                     int width, int height) {
        //rotate y
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstIndex = (width - x - 1) * height + y;
                dstY[dstIndex] = srcY[srcIndex++];
            }
        }

        //rotate uv
        int uvHeight = height / 2;
        int uvWidth = width / 2;
        int dstUVIndex = 0;
        int srcUVIndex = 0;
        for (int y = 0; y < uvHeight; y++) {
            for (int x = 0; x < uvWidth; x++) {
                dstUVIndex = (uvWidth - x - 1) * uvHeight + y;
                dstU[dstUVIndex] = srcU[srcUVIndex];
                dstV[dstUVIndex] = srcV[srcUVIndex];
                srcUVIndex++;
            }
        }
    }

    void
    rotateYUV420P(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
        unsigned char *pSrcY = src;
        unsigned char *pSrcU = src + width * height;
        unsigned char *pSrcV = src + width * height / 4 * 5;

        unsigned char *pDstY = dst;
        unsigned char *pDstU = dst + width * height;
        unsigned char *pDstV = dst + width * height / 4 * 5;

        if (degree == 90.0f) {
            rotateYUV420P90(pSrcY, pSrcU, pSrcV, pDstY, pDstU, pDstV, width, height);
        } else if (degree == 180.0f) {
            rotateYUV420P180(pSrcY, pSrcU, pSrcV, pDstY, pDstU, pDstV, width, height);
        } else if (degree == 270.0f) {
            rotateYUV420P270(pSrcY, pSrcU, pSrcV, pDstY, pDstU, pDstV, width, height);
        } else {
            return;
        }
    }

    static inline void
    rotateYUV420SP90(unsigned char *srcY, unsigned char *srcUV, unsigned char *dstY,
                     unsigned char *dstUV, int width, int height) {
        //rotate y
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstIndex = x * height + height - y - 1;
                dstY[dstIndex] = srcY[srcIndex++];
            }
        }

        //rotate uv
        int uvHeight = height >> 1;
        int uvWidth = width >> 1;
        int dstUVIndex = 0;
        int srcUVIndex = 0;
        for (int y = 0; y < uvHeight; y++) {
            for (int x = 0; x < uvWidth; x++) {
                dstUVIndex = (x * uvHeight + uvHeight - y - 1) << 1;
                dstUV[dstUVIndex] = srcUV[srcUVIndex++];
                dstUV[dstUVIndex + 1] = srcUV[srcUVIndex++];
            }
        }
    }

    static inline void
    rotateYUV420SP180(unsigned char *srcY, unsigned char *srcUV, unsigned char *dstY,
                      unsigned char *dstUV, int width, int height) {
        //rotate y
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstIndex = (height - y - 1) * width + width - x - 1;
                dstY[dstIndex] = srcY[srcIndex++];
            }
        }

        //rotate uv
        int uvHeight = height >> 1;
        int uvWidth = width >> 1;
        int dstUVIndex = 0;
        int srcUVIndex = 0;
        for (int y = 0; y < uvHeight; y++) {
            for (int x = 0; x < uvWidth; x++) {
                dstUVIndex = ((uvHeight - y - 1) * uvWidth + uvWidth - x - 1) << 1;
                dstUV[dstUVIndex] = srcUV[srcUVIndex++];
                dstUV[dstUVIndex + 1] = srcUV[srcUVIndex++];
            }
        }
    }

    static inline void
    rotateYUV420SP270(unsigned char *srcY, unsigned char *srcUV, unsigned char *dstY,
                      unsigned char *dstUV, int width, int height) {
        //rotate y
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                dstIndex = (width - x - 1) * height + y;
                dstY[dstIndex] = srcY[srcIndex++];
            }
        }

        //rotate uv
        int uvHeight = height >> 1;
        int uvWidth = width >> 1;
        int dstUVIndex = 0;
        int srcUVIndex = 0;
        for (int y = 0; y < uvHeight; y++) {
            for (int x = 0; x < uvWidth; x++) {
                dstUVIndex = ((uvWidth - x - 1) * uvHeight + y) << 1;
                dstUV[dstUVIndex] = srcUV[srcUVIndex++];
                dstUV[dstUVIndex + 1] = srcUV[srcUVIndex++];
            }
        }
    }

    void
    rotateYUV420SP(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
        unsigned char *pSrcY = src;
        unsigned char *pSrcUV = src + width * height;

        unsigned char *pDstY = dst;
        unsigned char *pDstUV = dst + width * height;

        if (degree == 90.0f) {
            rotateYUV420SP90(pSrcY, pSrcUV, pDstY, pDstUV, width, height);
        } else if (degree == 180.0f) {
            rotateYUV420SP180(pSrcY, pSrcUV, pDstY, pDstUV, width, height);
        } else if (degree == 270.0f) {
            rotateYUV420SP270(pSrcY, pSrcUV, pDstY, pDstUV, width, height);
        } else {
            return;
        }
    }

    static inline void
    rotateRGB90(unsigned char *src, unsigned char *dst, int width, int height, int bpp) {
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //(y, x) -> (x, height - y - 1)
                //y * width + x, -> x* height + height - y - 1
                dstIndex = (x * height + height - y - 1) * bpp;
                for (int i = 0; i < bpp; i++) {
                    dst[dstIndex + i] = src[srcIndex++];
                }
            }
        }
    }

    static inline void rotateRGB90(int *src, int *dst, int width, int height) {
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //(y, x) -> (x, height - y - 1)
                //y * width + x, -> x* height + height - y - 1
                dstIndex = x * height + height - y - 1;
                dst[dstIndex] = src[srcIndex++];
            }
        }
    }

    static inline void
    rotateRGB180(unsigned char *src, unsigned char *dst, int width, int height, int bpp) {
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //(y, x) -> (height - y - 1, width - x - 1)
                //y * width + x, -> (height - y - 1) * width + width - x - 1
                dstIndex = ((height - y - 1) * width + width - x - 1) * bpp;
                for (int i = 0; i < bpp; i++) {
                    dst[dstIndex + i] = src[srcIndex++];
                }
            }
        }
    }

    static inline void rotateRGB180(int *src, int *dst, int width, int height) {
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //(y, x) -> (height - y - 1, width - x - 1)
                //y * width + x, -> (height - y - 1) * width + width - x - 1
                dstIndex = (height - y - 1) * width + width - x - 1;
                dst[dstIndex] = src[srcIndex++];
            }
        }
    }

    static inline void
    rotateRGB270(unsigned char *src, unsigned char *dst, int width, int height, int bpp) {
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //(y, x) -> (width - x - 1, y)
                //y * width + x, -> (width - x - 1) * height + y
                dstIndex = ((width - x - 1) * height + y) * bpp;
                for (int i = 0; i < bpp; i++) {
                    dst[dstIndex + i] = src[srcIndex++];
                }
            }
        }
    }

    static inline void rotateRGB270(int *src, int *dst, int width, int height) {
        int dstIndex = 0;
        int srcIndex = 0;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                //(y, x) -> (width - x - 1, y)
                //y * width + x, -> (width - x - 1) * height + y
                dstIndex = (width - x - 1) * height + y;
                dst[dstIndex] = src[srcIndex++];
            }
        }
    }

    void rotateRGB(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
        if (degree == 90.0f) {
            rotateRGB90(src, dst, width, height, 3);
        } else if (degree == 180.0f) {
            rotateRGB180(src, dst, width, height, 3);
        } else if (degree == 270.0f) {
            rotateRGB270(src, dst, width, height, 3);
        } else {
            return;
        }
    }

    void rotateRGBA(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
        if (degree == 90.0f) {
            rotateRGB90(src, dst, width, height, 4);
        } else if (degree == 180.0f) {
            rotateRGB180(src, dst, width, height, 4);
        } else if (degree == 270.0f) {
            rotateRGB270(src, dst, width, height, 4);
        } else {
            return;
        }
    }

    void rotateRGBAInt(int *src, int *dst, int width, int height, float degree) {
        if (degree == 90.0f) {
            rotateRGB90(src, dst, width, height);
        } else if (degree == 180.0f) {
            rotateRGB180(src, dst, width, height);
        } else if (degree == 270.0f) {
            rotateRGB270(src, dst, width, height);
        } else {
            return;
        }
    }
}
