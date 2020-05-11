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

import static android.Manifest.permission.WRITE_EXTERNAL_STORAGE;
import static android.Manifest.permission.READ_EXTERNAL_STORAGE;


/**
 * @author Tyler Qiu
 * @date: 2020/05/09
 */
public class MainActivity extends AppCompatActivity {
    private static final String TAG = MainActivity.class.getSimpleName();

    private Handler mHandler;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mHandler = new Handler();
    }

    @Override
    protected void onResume() {
        super.onResume();
        if (checkSelfPermission(WRITE_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED
                || checkSelfPermission(READ_EXTERNAL_STORAGE) != PackageManager.PERMISSION_GRANTED) {
            Log.d(TAG, "requestPermissions");
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
                Log.d(TAG, "All permission granted.");
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
                default:
                    break;
            }
        }
    }

    private void convertByte(final int id) {
        TaskExecutor.run(new Runnable() {
            @Override
            public void run() {
                final String file;
                final byte[] yuv420;
                final int width = 3264;
                final int height = 2448;
                final byte[] rgba = new byte[width * height * 4];
                final Context context = MainActivity.this;
                Log.d(TAG, "convertByte---start");
                switch (id) {
                    case R.id.i420_to_rgba_byte:
                        file = "i420_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                        YUV2RGBAUtils.I420ToRGBAByte(yuv420, width, height, width, width / 2, 1, rgba);
                        break;
                    case R.id.yv12_to_rgba_byte:
                        file = "yv12_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.yv12_3264x2448);
                        YUV2RGBAUtils.YV12ToRGBAByte(yuv420, width, height, width, width / 2, 1, rgba);
                        break;
                    case R.id.nv12_to_rgba_byte:
                        file = "nv12_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv12_3264x2448);
                        YUV2RGBAUtils.NV12ToRGBAByte(yuv420, width, height, rgba);
                        break;
                    case R.id.nv21_to_rgba_byte:
                        file = "nv21_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv21_3264x2448);
                        YUV2RGBAUtils.NV21ToRGBAByte(yuv420, width, height, rgba);
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown format");
                }
                Log.d(TAG, "convertByte---end");
                final String fileName = "byte_" + file;
                final String parent = ImageUtils.getPicturesPath(context);
                Log.d(TAG, "RGBAToJPEG---start");
                ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
                Log.d(TAG, "RGBAToJPEG---end");

                //Log.d(TAG, "rotate---start");
                //final byte[] rotatedRgba = new byte[width * height * 4];
                //rotate 90
                //YUV2RGBAUtils.rotateByte(rgba, rotatedRgba, width, height, 4, 90.0f);
                //ImageUtils.RGBAToJPEG(context, rotatedRgba, height, width, parent, fileName);

                //rotate 180
                //YUV2RGBAUtils.rotateByte(rgba, rotatedRgba, width, height, 4, 180.0f);
                //ImageUtils.RGBAToJPEG(context, rotatedRgba, width, height, parent, fileName);

                //rotate 270
                //YUV2RGBAUtils.rotateByte(rgba, rotatedRgba, width, height, 4, 270.0f);
                //ImageUtils.RGBAToJPEG(context, rotatedRgba, height, width, parent, fileName);
                //Log.d(TAG, "rotate---end");
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
                final String file;
                final byte[] yuv420;
                final int width = 3264;
                final int height = 2448;
                final int[] rgba = new int[width * height];
                final Context context = MainActivity.this;
                Log.d(TAG, "convertByte---start");
                switch (id) {
                    case R.id.i420_to_rgba_int:
                        file = "i420_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.i420_3264x2448);
                        YUV2RGBAUtils.I420ToRGBAInt(yuv420, width, height, width, width / 2, 1, rgba);
                        break;
                    case R.id.yv12_to_rgba_int:
                        file = "yv12_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.yv12_3264x2448);
                        YUV2RGBAUtils.YV12ToRGBAInt(yuv420, width, height, width, width / 2, 1, rgba);
                        break;
                    case R.id.nv12_to_rgba_int:
                        file = "nv12_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv12_3264x2448);
                        YUV2RGBAUtils.NV12ToRGBAInt(yuv420, width, height, rgba);
                        break;
                    case R.id.nv21_to_rgba_int:
                        file = "nv21_3264x2448";
                        yuv420 = FileUtils.readRaw(context, R.raw.nv21_3264x2448);
                        YUV2RGBAUtils.NV21ToRGBAInt(yuv420, width, height, rgba);
                        break;
                    default:
                        throw new IllegalArgumentException("Unknown format");
                }
                Log.d(TAG, "convertInt---end");
                final String fileName = "int_" + file;
                final String parent = ImageUtils.getPicturesPath(context);
                Log.d(TAG, "RGBAToJPEG---start");
                ImageUtils.RGBAToJPEG(context, rgba, width, height, parent, fileName);
                Log.d(TAG, "RGBAToJPEG---end");

                //Log.d(TAG, "rotate---start");
                //final int[] rotatedRgba = new int[width * height];
                //rotate 90
                //YUV2RGBAUtils.rotateInt(rgba, rotatedRgba, width, height, 90.0f);
                //ImageUtils.RGBAToJPEG(context, rotatedRgba, height, width, parent, fileName);

                //rotate 180
                //YUV2RGBAUtils.rotateInt(rgba, rotatedRgba, width, height, 180.0f);
                //ImageUtils.RGBAToJPEG(context, rotatedRgba, width, height, parent, fileName);

                //rotate 270
                //YUV2RGBAUtils.rotateInt(rgba, rotatedRgba, width, height, 270.0f);
                //ImageUtils.RGBAToJPEG(context, rotatedRgba, height, width, parent, fileName);
                //Log.d(TAG, "rotate---end");
                mHandler.post(new Runnable() {
                    @Override
                    public void run() {
                        Toast.makeText(context, fileName + " convert finished!", Toast.LENGTH_LONG).show();
                    }
                });
            }
        });
    }
}
