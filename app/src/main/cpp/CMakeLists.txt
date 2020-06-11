#
# Copyright 2020 Tyler Qiu.
# YUV420 to RGBA open source project.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#       http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#

cmake_minimum_required(VERSION 3.4.1)

include_directories(${CMAKE_SOURCE_DIR}/include)

find_library(log-lib log)

add_library(
        NativeUtils
        SHARED
        native.cpp
        native_utils.cpp
)
target_link_libraries(NativeUtils ${log-lib})

add_library(opencv3 SHARED IMPORTED)
set_target_properties(
        opencv3
        PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libopencv_java3.so
)

add_library(
        OpencvUtils
        SHARED
        opencv.cpp
        opencv_utils.cpp
)
target_link_libraries(OpencvUtils opencv3 ${log-lib})

add_library(libyuv SHARED IMPORTED)
set_target_properties(
        libyuv
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libyuv.so
)

add_library(
        LibyuvUtils
        SHARED
        libyuv.cpp
        libyuv_utils.cpp
)
target_link_libraries(LibyuvUtils libyuv ${log-lib})