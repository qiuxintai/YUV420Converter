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

#ifndef CONVERT_UTILS_H
#define CONVERT_UTILS_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif
const int K_MAX_CHANNEL_VALUE = 262143;
const int YUV420P_I420 = 1;
const int YUV420P_YV12 = 2;
const int YUV420SP_NV12 = 3;
const int YUV420SP_NV21 = 4;

void YUV420PToRGBAByte(unsigned char* yuv420p, unsigned char* rgba, int width,
                       int height, int yRowStride, int uvRowStride, int uvPixelStride,
                       int format);

void YUV420PToRGBAInt(unsigned char* yuv420p, int* rgba, int width,
                      int height, int yRowStride, int uvRowStride, int uvPixelStride,
                      int format);

void YUV420SPToRGBAByte(unsigned char* yuv420sp, unsigned char* rgba, int width, int height,
                        int format);

void YUV420SPToRGBAInt(unsigned char* yuv420sp, int* rgba, int width, int height,
                       int format);

#ifdef __cplusplus
}
#endif

#endif //CONVERT_UTILS_H
