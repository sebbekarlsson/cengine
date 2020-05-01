#ifndef CENGINE_DRAW_H
#define CENGINE_DRAW_H
#include <GL/glew.h>
#include <cglm/cglm.h>


typedef struct DRAW_PROGRAM_STRUCT
{
    unsigned int VBO;
    unsigned int EBO;
    unsigned int shader_program;
    unsigned int generated;
} draw_program_T;

draw_program_T* init_draw_program(unsigned int shader_program);

draw_program_T* draw_program_genbuffers(draw_program_T* draw_program);

draw_program_T* draw_program_deletebuffers(draw_program_T* draw_program);

void draw_program_free(draw_program_T* draw_program);

void draw_quad(
    draw_program_T* draw_program,
    int width, int height,
    float x, float y, float z,
    float r, float g, float b, float a    
);

void draw_texture(
    draw_program_T* draw_program,
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
