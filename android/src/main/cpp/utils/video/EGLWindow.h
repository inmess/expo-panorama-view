//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_EGLWINDOW_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_EGLWINDOW_H

#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <android/native_window.h>
#include <android/native_window_jni.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>

class EGLWindow {
public:
    EGLWindow();
    ~EGLWindow();

    bool create(ANativeWindow *nativeWindow);

    bool makeCurrent();

    void release();

    bool swapBuffer();

    bool isReady();

private:
    EGLDisplay display = EGL_NO_DISPLAY;
    EGLContext context = EGL_NO_CONTEXT;
    EGLConfig config;
    EGLint numConfigs;
    EGLSurface surface = EGL_NO_SURFACE;

};
#endif //EXPO_PANORAMA_VIEW_EXAMPLE_EGLWINDOW_H
