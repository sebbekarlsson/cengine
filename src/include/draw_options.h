#ifndef CENGINE_DRAW_OPTIONS_H
#define CENGINE_DRAW_OPTIONS_H
#include <cglm/cglm.h>
#include "draw_program.h"

typedef struct DRAW_OPTIONS_STRUCT
{
    float x;
    float y;
    float z;
    float rx;
    float ry;
    float rz;
    float width;
    float height;
    float depth;
    float offset_x;
    float offset_y;
    float offset_z;
    unsigned int reverse;
    unsigned int flip_x;
    unsigned int flip_y;
    float r;
    float g;
    float b;
    float a;
    unsigned int texture;
    int atlas_width;
    int atlas_height;
    int shift_x;
    int shift_y;
} draw_options_T;

#define DRAW_OPTIONS_INIT {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.0f, 0, 0, 0, 0, 0}

void draw_options_get_matrix(draw_options_T draw_options, mat4 dest);
#endif
