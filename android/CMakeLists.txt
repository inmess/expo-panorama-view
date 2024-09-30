# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html.
# For more examples on how to use CMake, see https://github.com/android/ndk-samples.

# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 17)

add_definitions(-DOS_ANDROID)

# Declares the project name. The project name can be accessed via ${ PROJECT_NAME},
# Since this is the top level CMakeLists.txt, the project name is also accessible
# with ${CMAKE_PROJECT_NAME} (both CMake variables are in-sync within the top level
# build script scope).
project("panorama-player")

# set(ffmpeg_dir ${CMAKE_SOURCE_DIR}/../jniLibs)  # 设置ffmpeg_dir变量
# include_directories(${CMAKE_SOURCE_DIR}/ffmpeg)  # 设置需要include的头文件路径，注意这里的ANDROID_ABI代表了在gradle中指定的abiFilters的每一个变量
# set(ffmpeg_libs ${ffmpeg_dir}/${ANDROID_ABI}) # 设置ffmpeg_libs变量，指明shared library路径
# 

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(CPP_DIR ${SRC_DIR}/main/cpp)
set(EXT_LIB_DIR ${CMAKE_SOURCE_DIR}/jniLibs)
set(EXT_LIB_OBJECT_DIR ${EXT_LIB_DIR}/${ANDROID_ABI})
set(EXT_LIB_INCLUDES_DIR ${EXT_LIB_DIR}/includes)

file(GLOB CPP_FILES
        "${CPP_DIR}/*.cpp",
        "${CPP_DIR}/player/*.cpp",
        "${CPP_DIR}/utils/*.cpp",
        "${CPP_DIR}/utils/video/*.cpp",
        "${CPP_DIR}/utils/audio/*.cpp",
        "${CPP_DIR}/utils/video/render_logic/*.cpp",
)

include_directories("${CPP_DIR}/")
include_directories("${CPP_DIR}/player")
include_directories("${CPP_DIR}/interfaces")
include_directories("${CPP_DIR}/utils")
include_directories("${CPP_DIR}/utils/audio")
include_directories("${CPP_DIR}/utils/video")
include_directories("${CPP_DIR}/utils/video/render_logic")
include_directories("${CPP_DIR}/constants")

include_directories("${EXT_LIB_INCLUDES_DIR}/ffmpeg")
include_directories("${EXT_LIB_INCLUDES_DIR}")


add_library(avutil SHARED IMPORTED) # 声明avutil库
set_target_properties(
        avutil
        PROPERTIES IMPORTED_LOCATION
        ${EXT_LIB_OBJECT_DIR}/libavutil.so
) # 指定avutil库shared library路径

add_library(avformat SHARED IMPORTED) # 类似上面的声明
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libavformat.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libavfilter.so)

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libavcodec.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libswscale.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libswresample.so)

add_library(postproc SHARED IMPORTED)
set_target_properties(postproc PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libpostproc.so)

add_library(mp3lame SHARED IMPORTED)
set_target_properties(mp3lame PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libmp3lame.so)

#add_library(iconv SHARED IMPORTED)
#set_target_properties(iconv PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libiconv.so)

#add_library(hdr10plus SHARED IMPORTED)
#set_target_properties(hdr10plus PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libhdr10plus.so)

#add_library(fdk SHARED IMPORTED)
#set_target_properties(fdk PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libfdk-aac.so)

#add_library(charset SHARED IMPORTED)
#set_target_properties(charset PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libcharset.so)

add_library(aom SHARED IMPORTED)
set_target_properties(aom PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libaom.so)

add_library(x264 SHARED IMPORTED)
set_target_properties(x264 PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libx264.so)

add_library(x265 SHARED IMPORTED)
set_target_properties(x265 PROPERTIES IMPORTED_LOCATION ${EXT_LIB_OBJECT_DIR}/libx265.so)


#find_library(jnigraphics-lib jnigraphics) # 同上，使用jnigraphics

find_library(
        media-lib
        mediandk
)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
#
# In this top level CMakeLists.txt, ${CMAKE_PROJECT_NAME} is used to define
# the target library name; in the sub-module's CMakeLists.txt, ${PROJECT_NAME}
# is preferred for the same purpose.
#
# In order to load a library into your app from Java/Kotlin, you must call
# System.loadLibrary() and pass the name of the library defined here;
# for GameActivity/NativeActivity derived applications, the same library name must be
# used in the AndroidManifest.xml file.
add_library(${CMAKE_PROJECT_NAME} SHARED
        # List C/C++ source files with relative paths to this CMakeLists.txt.
        ${CPP_FILES})

find_package (oboe REQUIRED CONFIG)

# Specifies libraries CMake should link to your target library. You
# can link libraries from various origins, such as libraries defined in this
# build script, prebuilt third-party libraries, or Android system libraries.
target_link_libraries(${CMAKE_PROJECT_NAME}
        # List libraries link to the target library
#        ${jnigraphics-lib}
        ${media-lib}
        android
        oboe::oboe
        log
        OpenSLES
        GLESv3
        EGL
        z
        avutil
        avformat
        avfilter
        avcodec
        swscale
        swresample
        postproc
        mp3lame
#        iconv
#        hdr10plus
#        fdk
#        charset
        aom
        x264
        x265
)