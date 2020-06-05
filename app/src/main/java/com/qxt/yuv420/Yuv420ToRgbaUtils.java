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
public class Yuv420ToRgbaUtils {
    /*
     * YYYYYYYY UU VV    =>YUV420P
     * YYYYYYYY VV UU    =>YUV420P
     * YYYYYYYY UV UV    =>YUV420SP
     * YYYYYYYY VU VU    =>YUV420SP
     */
    static {
        System.loadLibrary("yuv2rgba");
        System.loadLibrary("convert");
    }

    /**
     * convert I420 to ARGB_8888
     *
     * @param yuv420p       src I420 byte array
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     * @param rgba          dst RGBA byte array, the length of the dst array must be >= width*height*4
     */
    public static native void I420ToRGBAByte(byte[] yuv420p, int width, int height, int yRowStride,
                                             int uvRowStride, int uvPixelStride, byte[] rgba);

    /**
     * convert I420 to ARGB_8888
     *
     * @param yuv420p       src I420 byte array
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     * @param rgba          dst RGBA int array, the length of the dst array must be >= width*height
     */
    public static native void I420ToRGBAInt(byte[] yuv420p, int width, int height, int yRowStride,
                                            int uvRowStride, int uvPixelStride, int[] rgba);

    /**
     * convert YV12 to ARGB_8888
     *
     * @param yuv420p       src YV12 byte array
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     * @param rgba          dst RGBA byte array, the length of the dst array must be >= width*height*4
     */
    public static native void YV12ToRGBAByte(byte[] yuv420p, int width, int height, int yRowStride,
                                             int uvRowStride, int uvPixelStride, byte[] rgba);

    /**
     * convert YV12 to ARGB_8888
     *
     * @param yuv420p       src YV12 byte array
     * @param width         image width
     * @param height        image height
     * @param yRowStride    The row stride of plane y.
     * @param uvRowStride   The row stride of plane u or v.
     * @param uvPixelStride The pixel stride of plane u or v.
     * @param rgba          dst RGBA int array, the length of the dst array must be >= width*height
     */
    public static native void YV12ToRGBAInt(byte[] yuv420p, int width, int height, int yRowStride,
                                            int uvRowStride, int uvPixelStride, int[] rgba);

    /**
     * convert NV12 to ARGB_8888
     *
     * @param yuv420sp src NV12 byte array
     * @param width    image width
     * @param height   image height
     * @param rgba     dst RGBA byte array, the length of the dst array must be >= width*height*4
     */
    public static native void NV12ToRGBAByte(byte[] yuv420sp, int width, int height, byte[] rgba);

    /**
     * convert NV12 to ARGB_8888
     *
     * @param yuv420sp src NV12 byte array
     * @param width    image width
     * @param height   image height
     * @param rgba     dst RGBA int array, the length of the dst array must be >= width*height
     */
    public static native void NV12ToRGBAInt(byte[] yuv420sp, int width, int height, int[] rgba);

    /**
     * convert NV21 to ARGB_8888
     *
     * @param yuv420sp src NV21 byte array
     * @param width    image width
     * @param height   image height
     * @param rgba     dst RGBA byte array, the length of the dst array must be >= width*height*4
     */
    public static native void NV21ToRGBAByte(byte[] yuv420sp, int width, int height, byte[] rgba);

    /**
     * convert NV21 to ARGB_8888
     *
     * @param yuv420sp src NV21 byte array
     * @param width    image width
     * @param height   image height
     * @param rgba     dst RGBA int array, the length of the dst array must be >= width*height
     */
    public static native void NV21ToRGBAInt(byte[] yuv420sp, int width, int height, int[] rgba);
}
