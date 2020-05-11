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
import android.content.Intent;
import android.net.Uri;
import android.text.TextUtils;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.ByteArrayOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;


/**
 * @author Tyler Qiu
 * @date: 2020/05/09
 */
public class FileUtils {
    private static final String TAG = FileUtils.class.getSimpleName();

    public static void scanFile(Context ctx, File file) {
        Intent scanIntent = new Intent(Intent.ACTION_MEDIA_SCANNER_SCAN_FILE);
        scanIntent.setData(Uri.fromFile(file));
        ctx.sendBroadcast(scanIntent);
    }

    public static int buildFile(Context ctx, String parent, String fileName) {
        if (TextUtils.isEmpty(parent) || TextUtils.isEmpty(fileName)) {
            Log.e(TAG, "Null args, parent:" + parent + ", fileName:" + fileName);
            return -1;
        }

        File path = new File(parent);
        if (!path.exists()) {
            if (!path.mkdirs()) {
                Log.e(TAG, "Failed to mkdir:" + parent);
                return -1;
            }
        }
        File file = new File(parent, fileName);
        if (!file.exists()) {
            try {
                if (file.createNewFile()) {
                    return 1;
                } else {
                    return 0;
                }
            } catch (IOException e) {
                e.printStackTrace();
                Log.e(TAG, "Failed to create file:" + parent + "/" + fileName);
                return -1;
            }
        } else {
            return 0;
        }
    }

    public static int writeFile(Context ctx, String parent, String fileName, byte[] data) {
        return writeFile(ctx, parent, fileName, data, false);
    }

    public static int writeFile(Context ctx, String parent, String fileName, byte[] data, boolean append) {
        int ret = buildFile(ctx, parent, fileName);
        if (ret >= 0) {
            FileOutputStream fos;
            try {
                File file = new File(parent, fileName);
                fos = new FileOutputStream(file, append);
                fos.write(data);
                fos.close();
                scanFile(ctx, file);
                ret = 1;
            } catch (IOException e) {
                e.printStackTrace();
                ret = -1;
                Log.e(TAG, "Failed to write file:" + parent + "/" + fileName);
            }
        }
        return ret;
    }

    public static byte[] readFile(String path) {
        if (TextUtils.isEmpty(path)) {
            return null;
        }

        File f = new File(path);
        if (!f.exists()) {
            return null;
        }

        ByteArrayOutputStream bos = null;
        BufferedInputStream bis = null;
        try {
            bos = new ByteArrayOutputStream((int) f.length());
            bis = new BufferedInputStream(new FileInputStream(f));
            int bufferSize = 1024;
            byte[] buffer = new byte[bufferSize];
            int len = 0;
            while (-1 != (len = bis.read(buffer, 0, bufferSize))) {
                bos.write(buffer, 0, len);
            }
            return bos.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                if (bis != null) {
                    bis.close();
                }
                if (bos != null) {
                    bos.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static byte[] readAssets(Context context, String fileName) {
        BufferedInputStream bis = null;
        ByteArrayOutputStream bos = null;
        try {
            bis = new BufferedInputStream(context.getAssets().open(fileName));
            bos = new ByteArrayOutputStream(bis.available());
            int bufferSize = 1024;
            byte[] buffer = new byte[bufferSize];
            int len = 0;
            while (-1 != (len = bis.read(buffer, 0, bufferSize))) {
                bos.write(buffer, 0, len);
            }
            return bos.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                if (bis != null) {
                    bis.close();
                }
                if (bos != null) {
                    bos.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public static byte[] readRaw(Context context, int rawId) {
        BufferedInputStream bis = null;
        ByteArrayOutputStream bos = null;
        try {
            bis = new BufferedInputStream(context.getResources().openRawResource(rawId));
            bos = new ByteArrayOutputStream(bis.available());
            int bufferSize = 1024;
            byte[] buffer = new byte[bufferSize];
            int len = 0;
            while (-1 != (len = bis.read(buffer, 0, bufferSize))) {
                bos.write(buffer, 0, len);
            }
            return bos.toByteArray();
        } catch (IOException e) {
            e.printStackTrace();
            return null;
        } finally {
            try {
                if (bis != null) {
                    bis.close();
                }
                if (bos != null) {
                    bos.close();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
