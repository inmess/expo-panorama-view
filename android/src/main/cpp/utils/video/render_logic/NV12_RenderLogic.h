//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_NV12_RENDERLOGIC_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_NV12_RENDERLOGIC_H

#pragma once

#include "IRenderLogic.h"
#include "RenderProgram.h"
#include "ShaderScripts.h"

class NV12_RenderLogic: public IRenderLogic{
public:
    NV12_RenderLogic();
    ~NV12_RenderLogic();

    const char *name() override;

    bool isReady() override;

    void render(VideoFrame *frame) override;

    void onFrameSizeChanged(int width, int height) override;

private:
    GLuint yBuffer, uvBuffer = 0;
    GLuint yTex = 0, uvTex = 0;

    RenderProgram renderProgram;

    void prepareObjects(int width, int height);

    void deleteObjects();
};


#endif //EXPO_PANORAMA_VIEW_EXAMPLE_NV12_RENDERLOGIC_H
