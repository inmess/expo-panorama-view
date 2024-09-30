//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_FACTORY_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_FACTORY_H


#include "PlayerContext.h"
#include "IDecoder.h"
#include "FFmpegDecoder.h"
#include "IAudioOutput.h"
#include "IVideoOutput.h"

#if defined(OS_ANDROID)
#include "audio/OboePlayer.h"
#include "video/OpenGLESPlayer2.h"
#elif defined(OS_IOS)

#elif defined(OS_WINDOWS)

#elif defined(OS_LINUX)

#endif


extern "C" {
#include "ffmpeg/libavformat/avformat.h"
}

IAudioOutput *getAudioOutput(PlayerContext *playerContext);
IVideoOutput *getVideoOutput(PlayerContext *playerContext);



#endif //EXPO_PANORAMA_VIEW_EXAMPLE_FACTORY_H
