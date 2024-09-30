//
// Created by 程宇栋 on 2024/8/30.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_PACKETWRAPPER_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_PACKETWRAPPER_H


extern "C" {
#include <ffmpeg/libavformat/avformat.h>
#include <ffmpeg/libavutil/avutil.h>
#include <ffmpeg/libavcodec/packet.h>
}
#include "Log.h"

#define TAG "PacketWrapper"

struct PacketWrapper {
    AVPacket *avPacket = nullptr;
    int32_t flags = 0;
    int rotate = 0;

    PacketWrapper() {
        flags = 0;
    }

    PacketWrapper(AVPacket *packet): PacketWrapper() {
        this->avPacket = packet;
    }

    PacketWrapper(const PacketWrapper &packetWrapper) = delete;

    PacketWrapper(PacketWrapper &&src) {
        this->avPacket = src.avPacket;
        this->flags = src.flags;
        src.avPacket = nullptr;
        src.flags = 0;
    }

    ~PacketWrapper() {
        //LOGD(TAG, "~PacketWrapper");
        if (avPacket != nullptr) {
            av_packet_unref(avPacket);
            av_packet_free(&avPacket);
            avPacket = nullptr;
        }
    }

    void setParams(AVPacket *packet) {
        reset();
        this->avPacket = packet;
    }

    void reset() {
        if (avPacket != nullptr) {
            av_packet_free(&avPacket);
            avPacket = nullptr;
        }

        flags = 0;
    }
};

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_PACKETWRAPPER_H
