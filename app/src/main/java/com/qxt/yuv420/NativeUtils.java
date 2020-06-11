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
 * @date: 2020/05/09
 */
public class NativeUtils {
    /*
     * YYYYYYYY UU VV    =>I420  =>YUV420P
     * YYYYYYYY VV UU    =>YV12  =>YUV420P
     * YYYYYYYY UV UV    =>NV12  =>YUV420SP
     * YYYYYYYY VU VU    =>NV21  =>YUV420SP
     */
    static {
        System.loadLibrary("NativeUtils");
    }

    /**
     * convert I420 to ARGB_8888
     *
     * @param src           src I420 byte array
     * @param dst           dst RGBA byte array, the length of the dst array must be >= width*height*4
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     */
    public static native void I420ToRGBAByte(byte[] src, byte[] dst, int width, int height,
                                             int yRowStride, int uvRowStride, int uvPixelStride);

    /**
     * convert I420 to ARGB_8888
     *
     * @param src           src I420 byte array
     * @param dst           dst RGBA int array, the length of the dst array must be >= width*height
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     */
    public static native void I420ToRGBAInt(byte[] src, int[] dst, int width, int height,
                                            int yRowStride, int uvRowStride, int uvPixelStride);

    /**
     * convert YV12 to ARGB_8888
     *
     * @param src           src YV12 byte array
     * @param dst           dst RGBA byte array, the length of the dst array must be >= width*height*4
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     */
    public static native void YV12ToRGBAByte(byte[] src, byte[] dst, int width, int height,
                                             int yRowStride, int uvRowStride, int uvPixelStride);

    /**
     * convert YV12 to ARGB_8888
     *
     * @param src           src YV12 byte array
     * @param dst           dst RGBA int array, the length of the dst array must be >= width*height
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     */
    public static native void YV12ToRGBAInt(byte[] src, int[] dst, int width, int height,
                                            int yRowStride, int uvRowStride, int uvPixelStride);

    /**
     * convert NV12 to ARGB_8888
     *
     * @param src      src NV12 byte array
     * @param dst      dst RGBA byte array, the length of the dst array must be >= width*height*4
     * @param width    image width
     * @param height   image height
     */
    public static native void NV12ToRGBAByte(byte[] src, byte[] dst, int width, int height);

    /**
     * convert NV12 to ARGB_8888
     *
     * @param src      src NV12 byte array
     * @param dst      dst RGBA int array, the length of the dst array must be >= width*height
     * @param width    image width
     * @param height   image height
     */
    public static native void NV12ToRGBAInt(byte[] src, int[] dst, int width, int height);

    /**
     * convert NV21 to ARGB_8888
     *
     * @param src      src NV21 byte array
     * @param dst      dst RGBA byte array, the length of the dst array must be >= width*height*4
     * @param width    image width
     * @param height   image height
     */
    public static native void NV21ToRGBAByte(byte[] src, byte[] dst, int width, int height);

    /**
     * convert NV21 to ARGB_8888
     *
     * @param src      src NV21 byte array
     * @param dst      dst RGBA int array, the length of the dst array must be >= width*height
     * @param width    image width
     * @param height   image height
     */
    public static native void NV21ToRGBAInt(byte[] src, int[] dst, int width, int height);

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
