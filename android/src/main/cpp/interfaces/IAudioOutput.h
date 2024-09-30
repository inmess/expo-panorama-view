//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_IAUDIOOUTPUT_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_IAUDIOOUTPUT_H

#include <stdlib.h>
#include "PlayerContext.h"
#include "AudioFrame.h"
extern "C" {
#include "ffmpeg/libavformat/avformat.h"
}

class IAudioOutput {
public:
    IAudioOutput(PlayerContext *playerContext) {
        this->playerCtx = playerContext;
    }

    virtual bool create(int sampleRate, int channels, AVSampleFormat sampleFormat) = 0;

    virtual void release() = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual bool write(AudioFrame *audioFrame) = 0;
    virtual void write(uint8_t *buffer, int framesPerChannel) = 0;

protected:
    PlayerContext *playerCtx = nullptr;
};
#endif //EXPO_PANORAMA_VIEW_EXAMPLE_IAUDIOOUTPUT_H
