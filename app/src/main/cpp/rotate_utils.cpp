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

#include "rotate_utils.h"

void rotateYUV420P(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    unsigned char *pSrcY = src;
    unsigned char *pSrcU = src + width * height;
    unsigned char *pSrcV = src + width * height / 4 * 5;

    unsigned char *pDstY = dst;
    unsigned char *pDstU = dst + width * height;
    unsigned char *pDstV = dst + width * height / 4 * 5;

    rotateYUV420P3(pSrcY, pSrcU, pSrcV, pDstY, pDstU, pDstV, width, height, degree);
}

void rotateYUV420P3(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
                   unsigned char *dstY, unsigned char *dstU, unsigned char *dstV,
                   int width, int height, float degree) {
    int dstIndex = 0;
    int srcIndex = 0;

    //rotate y
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
            dstY[dstIndex] = srcY[srcIndex];
        }
    }

    //rotate uv
    int uvHeight = height / 2;
    int uvWidth = width / 2;
    for (int y = 0; y < uvHeight; y++) {
        for (int x = 0; x < uvWidth; x++) {
            if (degree == 90.0f) {
                dstIndex = x * uvHeight + uvHeight - y - 1;
            } else if (degree == 180.0f) {
                dstIndex = (uvHeight - y - 1) * uvWidth + uvWidth - x - 1;
            } else if (degree == 270.0f) {
                dstIndex = (uvWidth - x - 1) * uvHeight + y;
            } else {
                dstIndex = y * uvWidth + x;
            }
            srcIndex = y * uvWidth + x;
            dstU[dstIndex] = srcU[srcIndex];
            dstV[dstIndex] = srcV[srcIndex];
        }
    }
}

void rotateYUV420SP(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    unsigned char *pSrcY = src;
    unsigned char *pSrcUV = src + width * height;

    unsigned char *pDstY = dst;
    unsigned char *pDstUV = dst + width * height;

    rotateYUV420SP2(pSrcY, pSrcUV, pDstY, pDstUV, width, height, degree);
}

void rotateYUV420SP2(unsigned char *srcY, unsigned char *srcUV,
                    unsigned char *dstY, unsigned char *dstUV,
                    int width, int height, float degree) {
    int dstIndex = 0;
    int srcIndex = 0;

    //rotate y
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
            dstY[dstIndex] = srcY[srcIndex];
        }
    }

    //rotate uv
    int uvHeight = height / 2;
    int uvWidth = width / 2;
    for (int y = 0; y < uvHeight; y++) {
        for (int x = 0; x < uvWidth; x ++) {
            if (degree == 90.0f) {
                dstIndex = x * uvHeight + uvHeight - y - 1;
            } else if (degree == 180.0f) {
                dstIndex = (uvHeight - y - 1) * uvWidth + uvWidth - x - 1;
            } else if (degree == 270.0f) {
                dstIndex = (uvWidth - x - 1) * uvHeight + y;
            } else {
                dstIndex = y * uvWidth + x;
            }
            srcIndex = y * uvWidth + x;
            dstUV[dstIndex * 2] = srcUV[srcIndex * 2];
            dstUV[dstIndex * 2 + 1] = srcUV[srcIndex * 2 + 1];
        }
    }
}

static inline void rotateRGB(unsigned char *src, unsigned char *dst, int width, int height, int bpp,
                             float degree) {
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
                dst[dstIndex + i] = src[srcIndex + i];
            }
        }
    }
}

void rotateRGB(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    rotateRGB(src, dst, width, height, 3, degree);
}

void rotateRGBA(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    rotateRGB(src, dst, width, height, 4, degree);
}

void rotateRGBAInt(int *src, int *dst, int width, int height, float degree) {
    int srcIndex = 0;
    int rotatedIndex = 0;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (degree == 90.0f) {
                //(y, x) -> (x, height - y - 1)
                //y * width + x, -> x* height + height - y - 1
                srcIndex = x * height + height - y - 1;
            } else if (degree == 180.0f) {
                //(y, x) -> (height - y - 1, width - x - 1)
                //y * width + x, -> (height - y - 1) * width + width - x - 1
                srcIndex = (height - y - 1) * width + width - x - 1;
            } else if (degree == 270.0f) {
                //(y, x) -> (width - x - 1, y)
                //y * width + x, -> (width - x - 1) * height + y
                srcIndex = (width - x - 1) * height + y;
            } else {
                srcIndex = y * width + x;
            }
            rotatedIndex = y * width + x;
            dst[srcIndex] = src[rotatedIndex];
        }
    }
}
