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

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.ImageFormat;
import android.graphics.Rect;
import android.graphics.YuvImage;
import android.media.Image;
import android.os.Environment;
import android.text.TextUtils;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.text.SimpleDateFormat;
import java.util.Locale;


/**
 * @author Tyler Qiu
 * @date: 2020/05/09
 */
public class ImageUtils {
    private static final String TAG = ImageUtils.class.getSimpleName();

    /*
     * For SPRD
     * YUV_420_888 is actually YUV422
     */
    public static byte[] convertYUV420888ToNV12(Image image) {
        ByteBuffer yBuffer = image.getPlanes()[0].getBuffer();
        ByteBuffer uvBuffer = image.getPlanes()[1].getBuffer();
        int yLength = yBuffer.remaining();
        int uvLength = uvBuffer.remaining();
        byte[] data = new byte[image.getWidth() * image.getHeight() * 3 / 2];
        yBuffer.get(data, 0, yLength);
        uvBuffer.get(data, yLength, uvLength);
        return data;
    }

    /*
     * For SPRD
     * YUV_420_888 is actually YUV422
     */
    public static byte[] convertYUV420888ToNV21(Image image) {
        ByteBuffer yBuffer = image.getPlanes()[0].getBuffer();
        ByteBuffer uvBuffer = image.getPlanes()[2].getBuffer();
        int yLength = yBuffer.remaining();
        int uvLength = uvBuffer.remaining();
        byte[] data = new byte[image.getWidth() * image.getHeight() * 3 / 2];
        yBuffer.get(data, 0, yLength);
        uvBuffer.get(data, yLength, uvLength);
        return data;
    }

    /*
     * For MTK
     * YUV_420_888 is actually I420
     */
    public static byte[] convertYUV420888ToI420(Image image) {
        int index = 0;
        final Image.Plane[] planes = image.getPlanes();
        byte[] yuvBytes = new byte[image.getWidth() * image.getHeight() * 3 / 2];
        for (Image.Plane plane : planes) {
            final ByteBuffer buffer = plane.getBuffer();
            int length = buffer.remaining();
            buffer.get(yuvBytes, index, length);
            buffer.clear();
            index += length;
        }
        return yuvBytes;
    }

    public static void RGBAToJPEG(Context context, byte[] rgba, int width, int height,
                                  String parentPath, String fileName) {
        saveRGBA(context, rgba, width, height, parentPath, fileName, Bitmap.CompressFormat.JPEG);
    }

    public static void RGBAToJPEG(Context context, int[] rgba, int width, int height,
                                  String parentPath, String fileName) {
        saveRGBA(context, rgba, width, height, parentPath, fileName, Bitmap.CompressFormat.JPEG);
    }

    public static void RGBAToPNG(Context context, byte[] rgba, int width, int height,
                                 String parentPath, String fileName) {
        saveRGBA(context, rgba, width, height, parentPath, fileName, Bitmap.CompressFormat.PNG);
    }

    public static void RGBAToPNG(Context context, int[] rgba, int width, int height,
                                 String parentPath, String fileName) {
        saveRGBA(context, rgba, width, height, parentPath, fileName, Bitmap.CompressFormat.PNG);
    }

    public static void RGBAToWEBP(Context context, byte[] rgba, int width, int height,
                                  String parentPath, String fileName) {
        saveRGBA(context, rgba, width, height, parentPath, fileName, Bitmap.CompressFormat.WEBP);
    }

    public static void RGBAToWEBP(Context context, int[] rgba, int width, int height,
                                  String parentPath, String fileName) {
        saveRGBA(context, rgba, width, height, parentPath, fileName, Bitmap.CompressFormat.WEBP);
    }

    private static void saveRGBA(Context context, byte[] rgba, int width, int height,
                                 String parentPath, String fileName, Bitmap.CompressFormat format) {
        Bitmap bitmap = null;
        ByteArrayOutputStream baos = null;
        ByteBuffer buffer = null;
        try {
            //Create bitmap
            bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
            buffer = ByteBuffer.wrap(rgba);
            bitmap.copyPixelsFromBuffer(buffer);//Convert YUV420 to byte array

            //Compress RGBA to JPEG/PNG/WEBP
            baos = new ByteArrayOutputStream();
            bitmap.compress(format, 100, baos);
            String path = checkParentPath(context, parentPath);
            String name = checkFileName(context, fileName, format);
            FileUtils.writeFile(context, path, name, baos.toByteArray());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (baos != null) {
                    baos.close();
                }

                if (buffer != null) {
                    buffer.clear();
                }

                if (bitmap != null && !bitmap.isRecycled()) {
                    bitmap.recycle();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    private static void saveRGBA(Context context, int[] rgba, int width, int height,
                                 String parentPath, String fileName, Bitmap.CompressFormat format) {
        Bitmap bitmap = null;
        ByteArrayOutputStream baos = null;
        try {
            //Create bitmap
            bitmap = Bitmap.createBitmap(width, height, Bitmap.Config.ARGB_8888);
            bitmap.setPixels(rgba, 0, width, 0, 0, width, height);

            //Compress RGBA to JPEG/PNG/WEBP
            baos = new ByteArrayOutputStream();
            bitmap.compress(format, 100, baos);
            String path = checkParentPath(context, parentPath);
            String name = checkFileName(context, fileName, format);
            FileUtils.writeFile(context, path, name, baos.toByteArray());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (baos != null) {
                    baos.close();
                }

                if (bitmap != null && !bitmap.isRecycled()) {
                    bitmap.recycle();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static void NV21ToJPEG(Context context, byte[] nv21, int width, int height,
                                  String parentPath, String fileName) {
        ByteArrayOutputStream baos = null;
        try {
            //Compress YUV420_NV21 to JPEG
            YuvImage image = new YuvImage(nv21, ImageFormat.NV21, width, height, null);
            baos = new ByteArrayOutputStream();
            image.compressToJpeg(new Rect(0, 0, width, height), 100, baos);

            //Save JPEG
            String path = checkParentPath(context, parentPath);
            String name = checkFileName(context, fileName, Bitmap.CompressFormat.JPEG);
            FileUtils.writeFile(context, path, name, baos.toByteArray());
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            try {
                if (baos != null) {
                    baos.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static String getPicturesPath(Context context) {
        /*File f = context.getExternalFilesDir(Environment.DIRECTORY_PICTURES);
        if (f != null) {
            return f.getAbsolutePath();
        } else {*/
        return Environment.getExternalStorageDirectory().getAbsolutePath() + "/Pictures";
        //}
    }

    private static String checkParentPath(Context context, String parent) {
        String path;
        if (TextUtils.isEmpty(parent)) {
            //Default output directory is "/sdcard/Pictures"
            return getPicturesPath(context);
        } else {
            return parent;
        }
    }

    private static String checkFileName(Context context, String fileName, Bitmap.CompressFormat format) {
        if (TextUtils.isEmpty(fileName)) {
            return new SimpleDateFormat("yyyyMMdd_HHmmss_SSS", Locale.getDefault())
                    .format(System.currentTimeMillis()) + "." + getExtension(format);
        } else {
            return fileName + "." + getExtension(format);
        }
    }

    private static String getExtension(Bitmap.CompressFormat format) {
        if (format == Bitmap.CompressFormat.JPEG) {
            return "jpg";
        } else if (format == Bitmap.CompressFormat.PNG) {
            return "png";
        } else if (format == Bitmap.CompressFormat.WEBP) {
            return "webp";
        } else {
            throw new IllegalArgumentException("Unknown compress format");
        }
    }
}
