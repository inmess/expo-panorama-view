#include <jni.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <android/log.h>

#include <JavaStateListener.h>
#include <Player.h>
#include <Log.h>

#define TAG "NATIVE_LIB"

using namespace std;



ANativeWindow *window = nullptr;
JavaStateListener *stateListener = nullptr;
Player *player = nullptr;

extern "C" JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_pInit(JNIEnv *env, jobject /* this */) {
    LOGD(TAG, "call nInit");
    if (player != nullptr) {
        return;
    }
    player = new Player();
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nDestroy(JNIEnv *env, jobject thiz) {
    LOGD(TAG, "call nDestroy");
    if (player == nullptr) {
        return;
    }
    player->pause();
    delete(player);
    player = nullptr;

    if (stateListener != nullptr) {
        delete(stateListener);
    }
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nStart(JNIEnv *env, jobject thiz) {
    LOGD(TAG, "call nStart");
    if(player == nullptr)
    {
        LOGE(TAG, "player is NULL when call nStart");
        return;
    }
    player->play();
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nStop(JNIEnv *env, jobject thiz) {
    LOGD(TAG, "call nStop");
    if(player == nullptr)
    {
        LOGE(TAG, "player is NULL when call nStop");
        return;
    }
    player->pause();
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nOpenFile(JNIEnv *env, jobject thiz,
                                                          jstring file_path) {
    LOGD(TAG, "nOpenFile");
    if(player == nullptr)
    {
        LOGE(TAG, "controller is NULL when call nOpenFile");
        return false;

    }
    const char *pathChars = env->GetStringUTFChars(file_path, NULL);

    bool result = player->openFile(pathChars);

    env->ReleaseStringUTFChars(file_path, pathChars);

    return result;
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nSetSurface(JNIEnv *env, jobject thiz,
                                                            jobject surface_view) {
    LOGD(TAG, "call nSetSurface");
    if(player == nullptr)
    {
        LOGE(TAG, "player is NULL when call nSetSurface");
        return;
    }
    window = ANativeWindow_fromSurface(env, surface_view);
    player->setWindow(window);
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nSetSize(JNIEnv *env, jobject thiz, jint width,
                                                         jint height) {
    LOGD(TAG, "call nSetSize");
    if(player == NULL)
    {
        LOGE(TAG, "controller is NULL when call nSetSize");
        return;
    }
    player->setScreenSize(width, height);
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nSeek(JNIEnv *env, jobject thiz, jlong position) {
    LOGD(TAG, "call nSeek");
    if(player == NULL)
    {
        LOGE(TAG, "controller is NULL when call nSetSize");
        return;
    }
    player->seek(position);
}
extern "C"
JNIEXPORT jlong JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nGetDuration(JNIEnv *env, jobject thiz) {
    LOGD(TAG, "call nGetDuration");
    if(player == NULL)
    {
        LOGE(TAG, "player is NULL when call nSetSize");
        return 0;
    }
    return player->getDurationMS();
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nSetPlayStateListener(JNIEnv *env, jobject thiz,
                                                                      jobject listener) {
    LOGD(TAG, "call nSetPlayStateListener");
    if(player == NULL)
    {
        LOGE(TAG, "player is NULL when call nSetSize");
        return;
    }
    if (stateListener == nullptr) {
        stateListener = new JavaStateListener(env, listener);
    }

    player->setPlayStateListener(stateListener);
}
extern "C"
JNIEXPORT void JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nRemovePlayStateListener(JNIEnv *env,
                                                                         jobject thiz) {
    LOGD(TAG, "call nRemovePlayStateListener");
    if(player == NULL)
    {
        LOGE(TAG, "player is NULL when call nSetSize");
        return;
    }

    player->removePlayStateListener();
    if(stateListener)
    {
        delete(stateListener);
        stateListener = nullptr;
    }
}
extern "C"
JNIEXPORT jboolean JNICALL
Java_expo_modules_panoramaview_ExpoPanoramaView_nIsPlaying(JNIEnv *env, jobject thiz) {
    LOGD(TAG, "call nIsPlaying");
    if(player == NULL)
    {
        LOGE(TAG, "player is NULL when call nSetSize");
        return false;
    }

    return player->isPlaying();
}