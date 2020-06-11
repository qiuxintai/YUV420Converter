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
#include <stdint.h>
#include <libyuv/convert.h>
#include <libyuv/convert_argb.h>
#include <libyuv/convert_from.h>
#include <libyuv/rotate.h>
#include <libyuv/rotate_argb.h>

#include "logger.h"
#include "libyuv_utils.h"

using namespace std;
using namespace libyuv;


void libyuvI420ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    unsigned char *pY = src;
    unsigned char *pU = src + width * height;
    unsigned char *pV = src + width * height * 5 / 4;
    I420ToABGR(pY, width, pU, width >> 1, pV, width >> 1, dst, width * 4, width, height);
}

void libyuvYV12ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    unsigned char *pY = src;
    unsigned char *pU = src + width * height * 5 / 4;
    unsigned char *pV = src + width * height;
    I420ToABGR(pY, width, pU, width >> 1, pV, width >> 1, dst, width * 4, width, height);
}

void libyuvNV12ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    unsigned char *pY = src;
    unsigned char *pUV = src + width * height;
    NV21ToARGB(pY, width, pUV, width, dst, width * 4, width, height);
}

void libyuvNV21ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    unsigned char *pY = src;
    unsigned char *pUV = src + width * height;
    NV12ToARGB(pY, width, pUV, width, dst, width * 4, width, height);
}

void libyuvRotateRGB(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    if (degree == 90.0f) {
        ARGBRotate(src, width * 3, dst, height * 3, width, height, kRotate90);
    } else if (degree == 180.0f) {
        ARGBRotate(src, width * 3, dst, width * 3, width, height, kRotate180);
    } else if (degree == 270.0f) {
        ARGBRotate(src, width * 3, dst, height * 3, width, height, kRotate270);
    } else {
        return;
    }
}

void libyuvRotateRGBA(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    if (degree == 90.0f) {
        ARGBRotate(src, width * 4, dst, height * 4, width, height, kRotate90);
    } else if (degree == 180.0f) {
        ARGBRotate(src, width * 4, dst, width * 4, width, height, kRotate180);
    } else if (degree == 270.0f) {
        ARGBRotate(src, width * 4, dst, height * 4, width, height, kRotate270);
    } else {
        return;
    }
}

void libyuvRotateYUV420P(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    unsigned char *pSrcY = src;
    unsigned char *pSrcU = src + width * height;
    unsigned char *pSrcV = src + width * height * 5 / 4;

    unsigned char *pDstY = dst;
    unsigned char *pDstU = dst + width * height;
    unsigned char *pDstV = dst + width * height * 5 / 4;

    if (degree == 90.0f) {
        I420Rotate(pSrcY, width, pSrcU, width >> 1, pSrcV, width >> 1,
                   pDstY, height, pDstU, height >> 1, pDstV, height >> 1,
                   width, height, kRotate90);
    } else if (degree == 180.0f) {
        I420Rotate(pSrcY, width, pSrcU, width >> 1, pSrcV, width >> 1,
                   pDstY, width, pDstU, width >> 1, pDstV, width >> 1,
                   width, height, kRotate180);
    } else if (degree == 270.0f) {
        I420Rotate(pSrcY, width, pSrcU, width >> 1, pSrcV, width >> 1,
                   pDstY, height, pDstU, height >> 1, pDstV, height >> 1,
                   width, height, kRotate270);
    } else {
        return;
    }
}

void libyuvRotateYUV420SP(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
    unsigned char *pSrcY = src;
    unsigned char *pSrcUV = src + width * height;

    unsigned char *pDstY = dst;
    unsigned char *pDstUV = dst + width * height;

    unsigned char *pTmp = new unsigned char[width * height * 3 / 2];
    unsigned char *pTmpY = pTmp;
    unsigned char *pTmpU = pTmp + width * height;
    unsigned char *pTmpV = pTmp + width * height * 5 / 4;

    if (degree == 90.0f) {
        NV12ToI420Rotate(pSrcY, width, pSrcUV, width,
                         pTmpY, height, pTmpU, height >> 1, pTmpV, height >> 1,
                         width, height, kRotate90);
        I420ToNV12(pTmpY, height, pTmpU, height >> 1, pTmpV, height >> 1,
                   pDstY, height, pDstUV, height, height, width);
    } else if (degree == 180.0f) {
        NV12ToI420Rotate(pSrcY, width, pSrcUV, width,
                         pTmpY, width, pTmpU, width >> 1, pTmpV, width >> 1,
                         width, height, kRotate180);
        I420ToNV12(pTmpY, width, pTmpU, width >> 1, pTmpV, width >> 1,
                   pDstY, width, pDstUV, width, width, height);
    } else if (degree == 270.0f) {
        NV12ToI420Rotate(pSrcY, width, pSrcUV, width,
                         pTmpY, height, pTmpU, height >> 1, pTmpV, height >> 1,
                         width, height, kRotate270);
        I420ToNV12(pTmpY, height, pTmpU, height >> 1, pTmpV, height >> 1,
                   pDstY, height, pDstUV, height, height, width);
    }
    delete[] pTmp;
}