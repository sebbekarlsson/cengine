#ifndef CENGINE_DRAW_H
#define CENGINE_DRAW_H
#include <GL/glew.h>
#include <cglm/cglm.h>
#include "draw_program.h"
#include "draw_options.h"


void draw_quad(
    draw_program_T* draw_program,
    draw_options_T draw_options
);

void draw_texture(
    draw_program_T* draw_program,
    draw_options_T draw_options
);

void draw_text(
    draw_program_T* draw_program,
    const char* text,
    const char* fontpath,
    float x, float y, float z,
    int size,
    float r, float g, float b
);

void draw_line(
    draw_program_T* draw_program,
    float x, float y, float z,
    float endx, float endy, float endz,
    float r, float g, float b, float a
);
#endif
