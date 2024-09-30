//
// Created by 程宇栋 on 2024/8/29.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_VIDEOFRAME_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_VIDEOFRAME_H


#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "Log.h"

extern "C" {
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavutil/avutil.h>
#include <ffmpeg/libavutil/display.h>
#include <ffmpeg/libavutil/frame.h>
}


// video frame
struct VideoFrame {
    const char* TAG = "VideoFrame";
    int width = -1;
    int height = -1;
    AVPixelFormat pixelFormat = AVPixelFormat::AV_PIX_FMT_NONE;
    AVFrame *avFrame = nullptr;
    int64_t pts = -1; // ms
    int64_t durationMS = -1;
    AVRational timeBase;
    int32_t flags = 0;
    // 视频方向相对于它应该显示的方向旋转了多少度。校正的话，取该值的负值
    int rotation = 0;

    VideoFrame() {

    }

    VideoFrame(AVFrame *avFrame, AVPixelFormat avPixelFormat, AVRational timeBase): VideoFrame() {
        setParams(avFrame, avPixelFormat, timeBase);
    }

    VideoFrame(VideoFrame &src) = delete;

    VideoFrame(VideoFrame &&src) {
        this->width = src.width;
        this->height = src.height;
        this->pixelFormat = src.pixelFormat;
        this->avFrame = src.avFrame;
        src.avFrame = nullptr;
        this->pts = src.pts;
        this->durationMS = src.durationMS;
        this->timeBase = src.timeBase;
        this->flags = src.flags;
        this->rotation = src.rotation;
    }

    ~VideoFrame() {
        //LOGD(TAG, "~VideoFrame");
        if (avFrame) {
            av_frame_unref(avFrame);
            av_frame_free(&avFrame);
            avFrame = nullptr;
        }
    }

    void setParams(AVFrame *avFrame, AVPixelFormat avPixelFormat, AVRational timeBase) {
        reset();
        this->avFrame = avFrame;
        this->pixelFormat = avPixelFormat;
        this->timeBase = timeBase;
        initParams();
    }

    void reset() {
        if (avFrame) {
            av_frame_free(&avFrame);
            avFrame = nullptr;
        }
        width = -1;
        height = -1;
        pixelFormat = AVPixelFormat::AV_PIX_FMT_NONE;
        pts = -1;
        durationMS = -1;
        flags = 0;
        rotation = 0;
    }

private:
    void initParams() {
        if (avFrame == nullptr) {
            return;
        }
        width = avFrame->width;
        height = avFrame->height;
        pts = avFrame->pts * av_q2d(timeBase) * 1000;
        durationMS = avFrame->pkt_duration * av_q2d(timeBase) * 1000;
        if (avFrame->nb_side_data > 0) {
            for (int i = 0; i < avFrame->nb_side_data; i++) {
                AVFrameSideData *sideData = avFrame->side_data[i];
                if (sideData->type == AV_FRAME_DATA_DISPLAYMATRIX) {
                    rotation = round(av_display_rotation_get((int32_t *)(sideData->data)));
                    // 取整，只支持90的倍数。
                    rotation = rotation / 90 * 90;
                }
            }
        }
        //LOGD(TAG, "rotation = %d", rotation);
        if (avFrame->nb_side_data > 0) {
            LOGD(TAG, "frame side_data > 0");
        }
    }

};


#endif //EXPO_PANORAMA_VIEW_EXAMPLE_VIDEOFRAME_H
