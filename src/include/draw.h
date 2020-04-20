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
    float a,
    int shift_x,
    int shift_y,
    int atlas_width,
    int atlas_height,
    unsigned int flip_x,
    unsigned int flip_y
);

void draw_text(
    unsigned int VAO,
    unsigned int VBO,
    unsigned int EBO,
    unsigned int shader_program,
    const char* text,
    const char* fontpath,
    float x, float y, float z,
    int size,
    float r, float g, float b
);
#endif
