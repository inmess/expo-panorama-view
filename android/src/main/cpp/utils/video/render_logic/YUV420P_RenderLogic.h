//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_YUV420P_RENDERLOGIC_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_YUV420P_RENDERLOGIC_H

#pragma once

#include "IRenderLogic.h"
#include "RenderProgram.h"
#include "ShaderScripts.h"

class YUV420P_RenderLogic: public IRenderLogic{
public:

    YUV420P_RenderLogic();
    ~YUV420P_RenderLogic();

    const char *name() override;

    bool isReady() override;

    void render(VideoFrame *frame) override;

    void onFrameSizeChanged(int width, int height) override;

private:
    GLuint yBuffer, uBuffer = 0, vBuffer = 0;
    GLuint yTex = 0, uTex = 0, vTex = 0;

    RenderProgram renderProgram;

    const static int GL_INTERNAL_FORMAT = GL_R8;
    const static int GL_FORMAT = GL_RED;
    const static int GL_DATA_TYPE = GL_UNSIGNED_BYTE;

    void prepareObjects(int width, int height);

    void deleteObjects();

};


#endif //EXPO_PANORAMA_VIEW_EXAMPLE_YUV420P_RENDERLOGIC_H
