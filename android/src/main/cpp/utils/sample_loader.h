//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_SAMPLE_LOADER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_SAMPLE_LOADER_H

#include <stdlib.h>
#include <stdint.h>
#include "SampleType.h"
#include "SampleLayout.h"
extern "C" {
#include "ffmpeg/libavformat/avformat.h"
#include "ffmpeg/libavutil/avutil.h"
}

SampleType get_sample_type(AVSampleFormat format);

SampleLayout get_sample_layout(AVSampleFormat format);

int64_t compute_buffer_size(AVSampleFormat format, int numChannel, int numFrame);

void merge_channels(uint8_t **src, int64_t startSampleIndex, uint8_t *dst, int sampleSize, int numChannel, int numFrame);

void separate_channels(uint8_t *src, int64_t startSampleIndex, uint8_t **dst, int sampleSize, int numChannel, int numFrame);



#endif //EXPO_PANORAMA_VIEW_EXAMPLE_SAMPLE_LOADER_H
