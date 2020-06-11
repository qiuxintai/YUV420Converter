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

#ifndef OPENCV_UTILS_H
#define OPENCV_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

void opencvI420ToRGBA(unsigned char *src, unsigned char *dst, int width, int height);

void opencvYV12ToRGBA(unsigned char *src, unsigned char *dst, int width, int height);

void opencvNV12ToRGBA(unsigned char *src, unsigned char *dst, int width, int height);

void opencvNV21ToRGBA(unsigned char *src, unsigned char *dst, int width, int height);

void opencvRotateRGB(unsigned char *src, int width, int height, float degree);

void opencvRotateRGBA(unsigned char *src, int width, int height, float degree);

void opencvRotateYUV420P(unsigned char *src, int width, int height, float degree);

#ifdef __cplusplus
}
#endif
#endif //OPENCV_UTILS_H
