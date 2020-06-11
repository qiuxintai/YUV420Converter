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
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "logger.h"
#include "opencv_utils.h"

using namespace std;
using namespace cv;

void opencvI420ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    Mat srcImg(height * 3 / 2, width, CV_8UC1, src);
    Mat dstImg(height, width, CV_8UC4, dst);
    cvtColor(srcImg, dstImg, CV_YUV2RGBA_I420);
}

void opencvYV12ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    Mat srcImg(height * 3 / 2, width, CV_8UC1, src);
    Mat dstImg(height, width, CV_8UC4, dst);
    cvtColor(srcImg, dstImg, CV_YUV2RGBA_YV12);
}

void opencvNV12ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    Mat srcImg(height * 3 / 2, width, CV_8UC1, src);
    Mat dstImg(height, width, CV_8UC4, dst);
    cvtColor(srcImg, dstImg, CV_YUV2RGBA_NV12);
}

void opencvNV21ToRGBA(unsigned char *src, unsigned char *dst, int width, int height) {
    Mat srcImg(height * 3 / 2, width, CV_8UC1, src);
    Mat dstImg(height, width, CV_8UC4, dst);
    cvtColor(srcImg, dstImg, CV_YUV2RGBA_NV21);
}

static inline void rotate(Mat srcImg, float degree, int stride) {
    Mat tmpImg;
    Mat finalImg;
    if (degree == 90.0f /*ROTATE_90_CLOCKWISE*/) {
        transpose(srcImg, tmpImg);
        flip(tmpImg, finalImg, 1);
    } else if (degree == 180.0f /*ROTATE_180*/) {
        flip(srcImg, finalImg, -1);
    } else if (degree == 270.0f /*ROTATE_90_COUNTERCLOCKWISE*/) {
        transpose(srcImg, tmpImg);
        flip(tmpImg, finalImg, 0);
    } else {
        return;
    }
    memcpy(srcImg.data, finalImg.data,
           static_cast<size_t>(finalImg.rows * finalImg.cols * stride));
    if (!tmpImg.empty()) {
        tmpImg.release();
    }

    if (!finalImg.empty()) {
        finalImg.release();
    }
}

void opencvRotateRGB(unsigned char *src, int width, int height, float degree) {
    Mat srcImg(height, width, CV_8UC3, src);
    rotate(srcImg, degree, 3);
}

void opencvRotateRGBA(unsigned char *src, int width, int height, float degree) {
    Mat srcImg(height, width, CV_8UC4, src);
    rotate(srcImg, degree, 4);
}

void opencvRotateYUV420P(unsigned char *src, int width, int height, float degree) {
    int uvWidth = width >> 1;
    int uvHeight = height >> 1;
    unsigned char *pY = src;
    unsigned char *pU = src + width * height;
    unsigned char *pV = src + width * height * 5 / 4;
    Mat y(height, width, CV_8UC1, pY);
    rotate(y, degree, 1);
    Mat u(uvHeight, uvWidth, CV_8UC1, pU);
    rotate(u, degree, 1);
    Mat v(uvHeight, uvWidth, CV_8UC1, pV);
    rotate(v, degree, 1);
}