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

static inline void rotateYUV420P90(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
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

static inline void rotateYUV420P180(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
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

static inline void rotateYUV420P270(unsigned char *srcY, unsigned char *srcU, unsigned char *srcV,
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

void rotateYUV420P(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
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

static inline void rotateYUV420SP90(unsigned char *srcY, unsigned char *srcUV, unsigned char *dstY,
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

static inline void rotateYUV420SP180(unsigned char *srcY, unsigned char *srcUV, unsigned char *dstY,
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

static inline void rotateYUV420SP270(unsigned char *srcY, unsigned char *srcUV, unsigned char *dstY,
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

void rotateYUV420SP(unsigned char *src, unsigned char *dst, int width, int height, float degree) {
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
