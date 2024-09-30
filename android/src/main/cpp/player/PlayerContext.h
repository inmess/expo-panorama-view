//
// Created by 程宇栋 on 2024/8/29.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_PLAYERCONTEXT_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_PLAYERCONTEXT_H


#include <stdio.h>
#include <stdlib.h>
#include <memory>
#include <thread>
#include "VideoFrame.h"
#include "AudioFrame.h"
#include "LinkedBlockingQueue.h"
#include "PacketWrapper.h"
#include "HandlerThread.h"

class PlayerContext {
public:
    PlayerContext();
    ~PlayerContext();

    VideoFrame* getEmptyVideoFrame();
    void recycleVideoFrame(VideoFrame *videoFrame);

    AudioFrame* getEmptyAudioFrame();
    void recycleAudioFrame(AudioFrame *audioFrame);

    PacketWrapper *getEmptyPacketWrapper();
    void recyclePacketWrapper(PacketWrapper *packetWrapper);

    void post(Runnable &&runnable);

    template<class Rep, class Period>
    void postDelayed(Runnable &&runnable, std::chrono::duration<Rep, Period> &&delay);

    template<class Clock, class Duration>
    void postAtTime(Runnable &&runnable, std::chrono::time_point<Clock, Duration> &&timePoint);

    void removeAll(Runnable &&runnable);
private:
    LinkedBlockingQueue<VideoFrame *> recycledVideoFrameQueue = LinkedBlockingQueue<VideoFrame *>(-1);
    LinkedBlockingQueue<AudioFrame *> recycledAudioFrameQueue = LinkedBlockingQueue<AudioFrame *>(-1);
    LinkedBlockingQueue<PacketWrapper *> recycledPacketWrapperQueue = LinkedBlockingQueue<PacketWrapper *>(-1);

    HandlerThread handlerThread;
};


#endif //EXPO_PANORAMA_VIEW_EXAMPLE_PLAYERCONTEXT_H
