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
package com.qxt.yuv420;


/**
 * @author Tyler Qiu
 * @date: 2020/06/04
 */
public class RotateUtils {
    static {
        System.loadLibrary("yuv2rgba");
        System.loadLibrary("rotate");
    }

    /**
     * rotate RGB image
     *
     * @param src    The input array.
     * @param dst    The output array.
     * @param width  The width of image.
     * @param height The height of image.
     * @param degree The rotate degree, must be 90.0f or 180.0f or 270.0f.
     */
    public static native void rotateRGB(byte[] src, byte[] dst, int width, int height, float degree);

    /**
     * rotate RGBA image
     *
     * @param src    The input array.
     * @param dst    The output array.
     * @param width  The width of image.
     * @param height The height of image.
     * @param degree The rotate degree, must be 90.0f or 180.0f or 270.0f.
     */
    public static native void rotateRGBA(byte[] src, byte[] dst, int width, int height, float degree);

    /**
     * rotate RGBA image
     *
     * @param src    The input array.
     * @param dst    The output array.
     * @param width  The width of image.
     * @param height The height of image.
     * @param degree The rotate degree, must be 90.0f or 180.0f or 270.0f.
     */
    public static native void rotateRGBAInt(int[] src, int[] dst, int width, int height, float degree);

    /**
     * rotate YUV420P image
     *
     * @param src    The input array.
     * @param dst    The output array.
     * @param width  The width of image.
     * @param height The height of image.
     * @param degree The rotate degree, must be 90.0f or 180.0f or 270.0f.
     */
    public static native void rotateYUV420P(byte[] src, byte[] dst, int width, int height, float degree);

    /**
     * rotate YUV420SP image
     *
     * @param src    The input array.
     * @param dst    The output array.
     * @param width  The width of image.
     * @param height The height of image.
     * @param degree The rotate degree, must be 90.0f or 180.0f or 270.0f.
     */
    public static native void rotateYUV420SP(byte[] src, byte[] dst, int width, int height, float degree);
}
