//
// Created by 程宇栋 on 2024/8/29.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_IPLAYSTATELISTENER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_IPLAYSTATELISTENER_H

#include <stdlib.h>
#include <stdint.h>

#define PLAY_STATE_START 0
#define PLAY_STATE_PAUSE 1
#define PLAY_STATE_COMPLETE 2
#define PLAY_STATE_SEEK_START 3
#define PLAY_STATE_SEEK_COMPLETE 4

class IPlayStateListener {
public:
    virtual void progressChanged(int64_t currentProgress) = 0;
    virtual void playStateChanged(int state) = 0;
};

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_IPLAYSTATELISTENER_H
