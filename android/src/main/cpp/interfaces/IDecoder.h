//
// Created by 程宇栋 on 2024/8/30.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_IDECODER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_IDECODER_H

#include <iostream>
#include <stdlib.h>
#include "CodecType.h"
#include "PreferCodecType.h"

extern "C" {
#include <ffmpeg/libavcodec/avcodec.h>
}

enum CodecState {
    OK, AGAIN, IS_EOF, NOT_INIT, UNKNOWN_ERROR
};

class IDecoder {
public:
    virtual ~IDecoder() {}
    virtual const char* getName() = 0;
    virtual bool init(AVCodecParameters *params, PreferCodecType preferType) = 0;
    virtual void release() = 0;
    virtual int sendPacket(const AVPacket *packet) = 0;
    virtual int receiveFrame(AVFrame *frame) = 0;
    virtual void flush() = 0;
    virtual CodecType getCodecType() = 0;
    virtual AVPixelFormat getPixelFormat() = 0;
};

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_IDECODER_H
