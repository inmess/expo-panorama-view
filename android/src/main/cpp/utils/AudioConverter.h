//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_AUDIOCONVERTER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_AUDIOCONVERTER_H


#include <stdlib.h>

#include "PlayerContext.h"
extern "C" {
#include "ffmpeg/libswresample/swresample.h"
}

class AudioConverter {
public:
    AudioConverter();
    ~AudioConverter();
    int setFormat(int srcSampleRate, int srcChannels, AVSampleFormat srcSampleFormat,
                  int dstSampleRate, int dstChannels, AVSampleFormat dstSampleFormat);

    void reset();

    size_t convert(uint8_t *inputBuffer, size_t inputSizeInBytes, uint8_t *outputBuffer, size_t outputBufferSizeInBytes);

private:

    SwrContext *swrContext = nullptr;

    int srcSampleRate = -1;
    int srcChannels = -1;
    AVSampleFormat srcSampleFormat = AVSampleFormat::AV_SAMPLE_FMT_NONE;
    int srcSampleSize = -1;

    int dstSampleRate = -1;
    int dstChannels = -1;
    AVSampleFormat dstSampleFormat = AVSampleFormat::AV_SAMPLE_FMT_NONE;
    int dstSampleSize = -1;


};

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_AUDIOCONVERTER_H
