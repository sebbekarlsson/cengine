#ifndef CENGINE_DRAW_PROGRAM_H
#define CENGINE_DRAW_PROGRAM_H

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

#endif
