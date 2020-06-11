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
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.View;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import static android.Manifest.permission.READ_EXTERNAL_STORAGE;
import static android.Manifest.permission.WRITE_EXTERNAL_STORAGE;


/**
 * @author Tyler Qiu
 * @date: 2020/05/09
 */
public class NativeTestActivity extends AppCompatActivity {
    private static final String TAG = NativeTestActivity.class.getSimpleName();

    private Handler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_native_test);
        mHandler = new Handler();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (checkSelfPermission(WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED
                || checkSelfPermission(READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            //Log.d(TAG, "requestPermissions");
            requestPermissions(new String[]{WRITE_EXTERNAL_STORAGE, READ_EXTERNAL_STORAGE}, 0);
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
    }


    @Override
    public void onRequestPermissionsResult(final int requestCode,
                                           @NonNull final String[] permissions,
                                           @NonNull final int[] grantResults) {
        if (requestCode == 0) {
            if (grantResults.length > 1
                    && grantResults[0] == PackageManager.PERMISSION_GRANTED
                    && grantResults[1] == PackageManager.PERMISSION_GRANTED) {
                //Log.d(TAG, "All permission granted.");
            } else {
                Toast.makeText(this, "Storage permission required!!!", Toast.LENGTH_LONG).show();
            }
        }
    }

    public void onClick(View view) {
        if (view != null) {
            int id = view.getId();
            switch (id) {
                case R.id.i420_to_rgba_byte:
                case R.id.yv12_to_rgba_byte:
                case R.id.nv12_to_rgba_byte:
                case R.id.nv21_to_rgba_byte:
                    convertByte(id);
                    break;
                case R.id.i420_to_rgba_int:
                case R.id.yv12_to_rgba_int:
                case R.id.nv12_to_rgba_int:
                case R.id.nv21_to_rgba_int:
                    convertInt(id);
                    break;
                case R.id.rotate_rgba:
                    rotateRGBA();
                    break;
                case R.id.rotate_rgba_int:
                    rotateRGBAInt();
                    break;
                case R.id.rotateYUV420P:
                    rotateYUV420P();
                    break;
                case R.id.rotateYUV420SP:
                    rotateYUV420SP();
                    break;
                default:
                    break;
            }
        }
    }

    private void convertByte(final int id) {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final byte[] yuv420;
                final int width = 3264;
                final int height = 2448;
                final byte[] rgba = new byte[width * height * 4];
                final Context context = NativeTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final String fileName;
                switch (id) {
                    case R.id.i420_to_rgba_byte:
                        fileName = "i420_3264x2448_convertByte";
                        yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                        long start = System.currentTimeMillis();
                        NativeUtils.I420ToRGBAByte(yuv420, rgba, width, height, width, width / 2, 1);
                        long end = System.currentTimeMillis();
                        Log.d(TAG, "[I420ToRGBAByte] cost time:" + (end - start));
                        break;
                    case R.id.yv12_to_rgba_byte:
                        fileName = "yv12_3264x2448_convertByte";
                        yuv420 = FileUtils.readRaw(context, R.raw.yv12_3264x2448);
                        NativeUtils.YV12ToRGBAByte(yuv420, rgba, width, height, width, width / 2, 1);
                        break;
                    case R.id.nv12_to_rgba_byte:
                        fileName = "nv12_3264x2448_convertByte";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv12_3264x2448);
                        NativeUtils.NV12ToRGBAByte(yuv420, rgba, width, height);
                        break;
                    case R.id.nv21_to_rgba_byte:
                        fileName = "nv21_3264x2448_convertByte";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv21_3264x2448);
                        long start2 = System.currentTimeMillis();
                        NativeUtils.NV21ToRGBAByte(yuv420, rgba, width, height);
                        long end2 = System.currentTimeMillis();
                        Log.d(TAG, "[NV21ToRGBAByte] cost time:" + (end2 - start2));
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown format");
                }
                ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, fileName + " convert finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }

    private void convertInt(final int id) {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final byte[] yuv420;
                final int width = 3264;
                final int height = 2448;
                final int[] rgba = new int[width * height];
                final Context context = NativeTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final String fileName;
                switch (id) {
                    case R.id.i420_to_rgba_int:
                        fileName = "i420_3264x2448_convertInt";
                        yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                        NativeUtils.I420ToRGBAInt(yuv420, rgba, width, height, width, width / 2, 1);
                        break;
                    case R.id.yv12_to_rgba_int:
                        fileName = "yv12_3264x2448_convertInt";
                        yuv420 = FileUtils.readRaw(context, R.raw.yv12_3264x2448);
                        NativeUtils.YV12ToRGBAInt(yuv420, rgba, width, height, width, width / 2, 1);
                        break;
                    case R.id.nv12_to_rgba_int:
                        fileName = "nv12_3264x2448_convertInt";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv12_3264x2448);
                        NativeUtils.NV12ToRGBAInt(yuv420, rgba, width, height);
                        break;
                    case R.id.nv21_to_rgba_int:
                        fileName = "nv21_3264x2448_convertInt";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv21_3264x2448);
                        NativeUtils.NV21ToRGBAInt(yuv420, rgba, width, height);
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown format");
                }
                ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, fileName + " convert finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }

    private void rotateRGBA() {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final int width = 3264;
                final int height = 2448;
                final Context context = NativeTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final float rotationDegree = 90.0f;//180.0f;//270.0f;
                final String fileName = "i420_3264x2448_rotateRGBA_" + rotationDegree;
                final byte[] yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                final byte[] rgba = new byte[width * height * 4];
                final byte[] rotatedRgba = new byte[width * height * 4];
                NativeUtils.I420ToRGBAByte(yuv420, rgba, width, height, width, width / 2, 1);
                long start = System.currentTimeMillis();
                NativeUtils.rotateRGBA(rgba, rotatedRgba, width, height, rotationDegree);
                long end = System.currentTimeMillis();
                Log.d(TAG, "[rotateRGBA] cost time:" + (end - start));
                if (rotationDegree == 90.0f || rotationDegree == 270.0f) {
                    ImageUtils.RGBAToJPEG(context, rotatedRgba, height, width, parent, fileName);
                } else if (rotationDegree == 180.0f) {
                    ImageUtils.RGBAToJPEG(context, rotatedRgba, width, height, parent, fileName);
                }
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, "Test rotateRGBA finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }

    private void rotateRGBAInt() {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final int width = 3264;
                final int height = 2448;
                final int[] rgba = new int[width * height];
                final Context context = NativeTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final float rotationDegree = 90.0f;//180.0f;//270.0f;
                final String fileName = "i420_3264x2448_rotateRGBAInt_" + rotationDegree;
                final byte[] yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                final int[] rotatedRgba = new int[width * height];
                NativeUtils.I420ToRGBAInt(yuv420, rgba, width, height, width, width / 2, 1);
                NativeUtils.rotateRGBAInt(rgba, rotatedRgba, width, height, rotationDegree);
                if (rotationDegree == 90.0f || rotationDegree == 270.0f) {
                    ImageUtils.RGBAToJPEG(context, rotatedRgba, height, width, parent, fileName);
                } else if (rotationDegree == 180.0f) {
                    ImageUtils.RGBAToJPEG(context, rotatedRgba, width, height, parent, fileName);
                }
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, "Test rotateRGBAInt finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }

    private void rotateYUV420P() {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final int width = 3264;
                final int height = 2448;
                final Context context = NativeTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final float rotationDegree = 90.0f;//180.0f;//270.0f;
                final String fileName = "i420_3264x2448_rotateYUV420P_" + rotationDegree;
                final byte[] yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                final byte[] rotatedYUV420 = new byte[width * height * 3 / 2];
                final int[] rgba = new int[width * height];
                long start = System.currentTimeMillis();
                NativeUtils.rotateYUV420P(yuv420, rotatedYUV420, width, height, rotationDegree);
                long end = System.currentTimeMillis();
                Log.d(TAG, "[rotateYUV420P] cost time:" + (end - start));
                if (rotationDegree == 90.0f || rotationDegree == 270.0f) {
                    NativeUtils.I420ToRGBAInt(rotatedYUV420, rgba, height, width, height, height / 2, 1);
                    ImageUtils.RGBAToJPEG(context, rgba, height, width, parent, fileName);
                } else if (rotationDegree == 180.0f) {
                    NativeUtils.I420ToRGBAInt(rotatedYUV420, rgba, width, height, width, width / 2, 1);
                    ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
                }
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, "Test rotateYUV420P finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }

    private void rotateYUV420SP() {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final int width = 3264;
                final int height = 2448;
                final Context context = NativeTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final float rotationDegree = 90.0f;//180.0f;//270.0f;
                final String fileName = "nv12_3264x2448_rotateYUV420SP_" + rotationDegree;
                final byte[] yuv420 = FileUtils.readRaw(context, R.raw.nv12_3264x2448);
                final byte[] rotatedYUV420 = new byte[width * height * 3 / 2];
                final int[] rgba = new int[width * height];
                NativeUtils.rotateYUV420SP(yuv420, rotatedYUV420, width, height, rotationDegree);
                if (rotationDegree == 90.0f || rotationDegree == 270.0f) {
                    NativeUtils.NV12ToRGBAInt(rotatedYUV420, rgba, height, width);
                    ImageUtils.RGBAToJPEG(context, rgba, height, width, parent, fileName);
                } else if (rotationDegree == 180.0f) {
                    NativeUtils.NV12ToRGBAInt(rotatedYUV420, rgba, width, height);
                    ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
                }
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, "Test rotateYUV420SP finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }
}
