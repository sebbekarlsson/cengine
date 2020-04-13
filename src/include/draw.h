#ifndef CENGINE_DRAW_H
#define CENGINE_DRAW_H
#include <GL/glew.h>
#include <cglm/cglm.h>

void draw_texture(
    unsigned int VBO,
    unsigned int EBO,
    unsigned int shader_program,
    unsigned int texture,
    float x, float y, float z,
    int width,
    int height,
    float r,
    float g,
    float b,
    float a
);
#endif
