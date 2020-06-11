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
public class OpencvTestActivity extends AppCompatActivity {
    private static final String TAG = OpencvTestActivity.class.getSimpleName();

    private Handler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_opencv_test);
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
                case R.id.I420ToRGBA:
                case R.id.YV12ToRGBA:
                case R.id.NV12ToRGBA:
                case R.id.NV21ToRGBA:
                    convert(id);
                    break;
                case R.id.rotateRGBA:
                    rotateRGBA();
                    break;
                case R.id.rotateYUV420P:
                    rotateYUV420P();
                    break;
                default:
                    break;
            }
        }
    }

    private void convert(final int id) {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final byte[] yuv420;
                final int width = 3264;
                final int height = 2448;
                final byte[] rgba = new byte[width * height * 4];
                final Context context = OpencvTestActivity.this;
                final String fileName;
                switch (id) {
                    case R.id.I420ToRGBA:
                        fileName = "i420_3264x2448_opencv";
                        yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                        long start = System.currentTimeMillis();
                        OpencvUtils.I420ToRGBA(yuv420, rgba, width, height);
                        long end = System.currentTimeMillis();
                        Log.d(TAG, "[opencvI420ToRGBA] cost time:" + (end - start));
                        break;
                    case R.id.YV12ToRGBA:
                        fileName = "yv12_3264x2448_opencv";
                        yuv420 = FileUtils.readRaw(context, R.raw.yv12_3264x2448);
                        OpencvUtils.YV12ToRGBA(yuv420, rgba, width, height);
                        break;
                    case R.id.NV12ToRGBA:
                        fileName = "nv12_3264x2448_opencv";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv12_3264x2448);
                        OpencvUtils.NV12ToRGBA(yuv420, rgba, width, height);
                        break;
                    case R.id.NV21ToRGBA:
                        fileName = "nv21_3264x2448_opencv";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv21_3264x2448);
                        long start2 = System.currentTimeMillis();
                        OpencvUtils.NV21ToRGBA(yuv420, rgba, width, height);
                        long end2 = System.currentTimeMillis();
                        Log.d(TAG, "[opencvNV21ToRGBA] cost time:" + (end2 - start2));
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown format");
                }
                final String parent = ImageUtils.getPicturesPath(context);
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
                final Context context = OpencvTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final float rotationDegree = 270.0f;//180.0f;//270.0f;
                final String fileName = "i420_3264x2448_opencv_rotateRGBA_" + rotationDegree;
                final byte[] yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                final byte[] rgba = new byte[width * height * 4];
                OpencvUtils.I420ToRGBA(yuv420, rgba, width, height);
                long start = System.currentTimeMillis();
                OpencvUtils.rotateRGBA(rgba, width, height, rotationDegree);
                long end = System.currentTimeMillis();
                Log.d(TAG, "[opencvRotateRGBA] cost time:" + (end - start));
                if (rotationDegree == 90.0f || rotationDegree == 270.0f) {
                    ImageUtils.RGBAToJPEG(context, rgba, height, width, parent, fileName);
                } else if (rotationDegree == 180.0f) {
                    ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
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

    private void rotateYUV420P() {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final int width = 3264;
                final int height = 2448;
                final Context context = OpencvTestActivity.this;
                final String parent = ImageUtils.getPicturesPath(context);
                final float rotationDegree = 270.0f;//180.0f;//270.0f;
                final String fileName = "i420_3264x2448_opencv_rotateYUV420P_" + rotationDegree;
                final byte[] yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                final byte[] rgba = new byte[width * height * 4];
                long start = System.currentTimeMillis();
                OpencvUtils.rotateYUV420P(yuv420, width, height, rotationDegree);
                long end = System.currentTimeMillis();
                Log.d(TAG, "[opencvRotateYUV420P] cost time:" + (end - start));
                if (rotationDegree == 90.0f || rotationDegree == 270.0f) {
                    OpencvUtils.I420ToRGBA(yuv420, rgba, height, width);
                    ImageUtils.RGBAToJPEG(context, rgba, height, width, parent, fileName);
                } else if (rotationDegree == 180.0f) {
                    OpencvUtils.I420ToRGBA(yuv420, rgba, width, height);
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
}
