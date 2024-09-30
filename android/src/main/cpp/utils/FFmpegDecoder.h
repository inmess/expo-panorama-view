//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_FFMPEGDECODER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_FFMPEGDECODER_H


#include "IDecoder.h"
#include "platform.h"

extern "C" {
#include "ffmpeg/libavcodec/avcodec.h"
#include "ffmpeg/libavutil/hwcontext.h"
};

class FFmpegDecoder: public IDecoder{
public:

    FFmpegDecoder();

    ~FFmpegDecoder();

    const char* getName();

    bool init(AVCodecParameters *params, PreferCodecType preferType);

    void release();

    int sendPacket(const AVPacket *packet);

    int receiveFrame(AVFrame *frame);

    void flush();

    CodecType getCodecType();

    AVPixelFormat getPixelFormat();

private:

    AVCodecContext *codecCtx = nullptr;
    AVCodec *codec = nullptr;
    CodecType codecType = CodecType::UNKNOWN;

    // hw
    AVBufferRef *hwDeviceCtx = nullptr;
    AVPixelFormat hwPixFormat = AV_PIX_FMT_NONE;

    int initHWDecoder(AVCodecContext *ctx, const enum AVHWDeviceType type);

    bool findHWDecoder(AVCodecParameters *params, AVCodecID codecId);

    bool findSWDecoder(AVCodecParameters *params, AVCodecID codecId);

};




#endif //EXPO_PANORAMA_VIEW_EXAMPLE_FFMPEGDECODER_H
