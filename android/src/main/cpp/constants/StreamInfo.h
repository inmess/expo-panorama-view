//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_STREAMINFO_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_STREAMINFO_H

#include <stdio.h>
#include <stdlib.h>
#include "CodecType.h"
extern "C" {
#include "ffmpeg/libavcodec/avcodec.h"
};

struct StreamInfo {

    int streamIndex = -1;
    AVMediaType type = AVMEDIA_TYPE_UNKNOWN;

    CodecType codecType = CodecType::UNKNOWN;

    // audio
    int32_t sampleRate = -1;
    int32_t channels = -1;
    AVSampleFormat sampleFormat = AVSampleFormat::AV_SAMPLE_FMT_NONE;

    // video
    int32_t width = -1;
    int32_t height = -1;
    float fps = -1;
    AVPixelFormat pixelFormat = AVPixelFormat::AV_PIX_FMT_NONE;
    int rotate = 0;

};


#endif //EXPO_PANORAMA_VIEW_EXAMPLE_STREAMINFO_H
