//
// Created by 程宇栋 on 2024/8/29.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_JAVASTATELISTENER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_JAVASTATELISTENER_H

#include <jni.h>
#include <stdlib.h>
#include <iostream>
#include "../interfaces/IPlayStateListener.h"

using namespace std;

class JavaStateListener: public IPlayStateListener {
public:
    JavaStateListener(JNIEnv *env, jobject listener);
    ~JavaStateListener();
    void progressChanged(int64_t currentProgress) override;
    void playStateChanged(int state) override;
private:
//    JNIEnv *env = NULL;
    JavaVM *vm = NULL;
    jobject listener = NULL;
//    jmethodID infoGetMethod = NULL;
    jmethodID progressChangedMethod = NULL;
    jmethodID playStateChangedMethod = NULL;
};

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_JAVASTATELISTENER_H
