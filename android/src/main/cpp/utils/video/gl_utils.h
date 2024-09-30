//
// Created by 程宇栋 on 2024/9/19.
//

#ifndef EXPO_PANORAMA_VIEW_EXAMPLE_GL_UTILS_H
#define EXPO_PANORAMA_VIEW_EXAMPLE_GL_UTILS_H

#include <iostream>
#include <stdlib.h>
#include <GLES3/gl31.h>
#include <GLES3/gl3platform.h>
#include "SizeMode.h"

void create_vertex_objects(GLuint &VAO, GLuint &VBO, GLuint &EBO, float *vertexData, unsigned int *indices);

bool compute_vertex(int screenWidth, int screenHeight, int imageWidth, int imageHeight, int orientation, SizeMode sizeMode, float *result);

#endif //EXPO_PANORAMA_VIEW_EXAMPLE_GL_UTILS_H
