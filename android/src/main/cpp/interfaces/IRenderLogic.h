//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_IRENDERLOGIC_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_IRENDERLOGIC_H

#pragma once

#include <iostream>
#include <stdlib.h>
#include <GLES3/gl31.h>
#include <GLES3/gl3platform.h>
#include "VideoFrame.h"
#include "gl_data.h"
#include "gl_utils.h"
#include "SizeMode.h"

class IRenderLogic {
public:
    virtual ~IRenderLogic() {
        deleteVertex();
    }
    virtual const char* name() = 0;

    virtual bool isReady() = 0;

    virtual void config(
            int screenWidth, int screenHeight,
            int frameWidth, int frameHeight,
            int orientation, SizeMode sizeMode) {

        if (this->screenWidth != screenWidth || this->screenHeight != screenHeight
            || this->frameWidth != frameWidth || this->frameHeight != frameHeight
            || this->sizeMode != sizeMode || this->rotation != orientation) {

            bool frameSizeSame = this->frameWidth == frameWidth && this->frameHeight == frameHeight;

            this->screenWidth = screenWidth;
            this->screenHeight = screenHeight;
            this->frameWidth = frameWidth;
            this->frameHeight = frameHeight;
            this->rotation = orientation;
            this->sizeMode = sizeMode;
            updateVertex();
            if (!frameSizeSame) {
                onFrameSizeChanged(frameWidth, frameHeight);
            }
        }

    }

    virtual void setFrameSize(int width, int height) {
        if (frameWidth != width || frameHeight != height) {
            frameWidth = width;
            frameHeight = height;
            updateVertex();
            onFrameSizeChanged(width, height);
        }
    };

    virtual void setScreenSize(int width, int height) {
        if (screenWidth != width || screenHeight != height) {
            screenWidth = width;
            screenHeight = height;
            updateVertex();
        }
    }

    virtual void setSizeMode(SizeMode mode) {
        if (sizeMode != mode) {
            sizeMode = mode;
            updateVertex();
        }
    }

    virtual void setRotation(int degree) {
        if (rotation != degree) {
            rotation = degree;
            updateVertex();
        }
    };

    virtual void render(VideoFrame *frame) = 0;

    virtual void onFrameSizeChanged(int width, int height) {

    }

    int getRotation() {
        return rotation;
    }

    int getScreenWidth() {
        return screenWidth;
    }

    int getScreenHeight() {
        return screenHeight;
    }

    int getFrameWidth() {
        return frameWidth;
    }

    int getFrameHeight() {
        return frameHeight;
    }
protected:
    int frameHeight = 1080;
    int frameWidth = 1920;
    int screenHeight = 1080;
    int screenWidth = 1920;
    SizeMode sizeMode = SizeMode::FIT;
    int rotation = 0;

    GLuint VAO = 0, VBO = 0, EBO = 0;

    virtual void updateVertex() {
        deleteVertex();
        float vertexData[20];
        compute_vertex(screenWidth, screenHeight, frameWidth, frameHeight, rotation, sizeMode, vertexData);
        create_vertex_objects(VAO, VBO, EBO, vertexData, EBO_indices);
    }

    virtual void deleteVertex() {
        if (VAO) {
            glDeleteVertexArrays(1, &VAO);
        }
        if (VBO) {
            glDeleteBuffers(1, &VBO);
        }
        if (EBO) {
            glDeleteBuffers(1, &EBO);
        }
    }
};
#endif //EXPO_PANORAMA_VIEW_EXAMPLE_IRENDERLOGIC_H
