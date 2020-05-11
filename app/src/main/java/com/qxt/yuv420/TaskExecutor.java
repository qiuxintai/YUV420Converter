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

import java.util.concurrent.BlockingQueue;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.ThreadPoolExecutor;
import java.util.concurrent.TimeUnit;


/**
 * @author Tyler Qiu
 * @date: 2020/05/09
 */
public class TaskExecutor {
    private static final TaskExecutor sInstance;
    private ThreadPoolExecutor mThreadPoolExecutor;
    private BlockingQueue<Runnable> mWorkQueue;

    static {
        sInstance = new TaskExecutor();
    }

    public static TaskExecutor getInstance() {
        return sInstance;
    }

    private TaskExecutor() {
        mWorkQueue = new LinkedBlockingQueue<>();
        mThreadPoolExecutor = new ThreadPoolExecutor(
                2,
                4,
                1,
                TimeUnit.SECONDS,
                mWorkQueue);

    }

    public static void run(Runnable task) {
        sInstance.mThreadPoolExecutor.execute(task);
    }
}
