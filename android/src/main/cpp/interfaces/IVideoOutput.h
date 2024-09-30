//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_IVIDEOOUTPUT_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_IVIDEOOUTPUT_H

#include <stdlib.h>
#include "VideoFrame.h"
#include "PlayerContext.h"
#include "SizeMode.h"

class IVideoOutput {
public:
    IVideoOutput(PlayerContext *playerContext) {
        this->playerCtx = playerContext;
    };
    virtual bool setFormat(AVPixelFormat pixelFormat, AVColorSpace colorSpace, bool isHDR) = 0;
    virtual bool create(void *surface) = 0;
    virtual void release() = 0;
    virtual void setScreenSize(int32_t width, int32_t height) = 0;
    virtual bool isReady() = 0;
    virtual void write(VideoFrame* frame) = 0;
    virtual void setSizeMode(SizeMode mode) = 0;

protected:
    PlayerContext *playerCtx;
    AVPixelFormat srcPixelFormat = AVPixelFormat::AV_PIX_FMT_NONE;
};

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_IVIDEOOUTPUT_H
