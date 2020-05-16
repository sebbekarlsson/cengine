#include "include/draw_program.h"
#include <stdlib.h>
#include <GL/glew.h>


draw_program_T* init_draw_program(unsigned int shader_program)
{
    draw_program_T* draw_program = calloc(1, sizeof(struct DRAW_PROGRAM_STRUCT));
    draw_program->shader_program = shader_program;
    draw_program->generated = 0;

    return draw_program;
}

draw_program_T* draw_program_genbuffers(draw_program_T* draw_program)
{
    glGenBuffers(1, &draw_program->VBO);
    glGenBuffers(1, &draw_program->EBO);

    draw_program->generated = 1;

    return draw_program;
}

draw_program_T* draw_program_deletebuffers(draw_program_T* draw_program)
{
    if (!draw_program->generated)
        return draw_program;

    glDeleteBuffers(1, &draw_program->VBO);
    glDeleteBuffers(1, &draw_program->EBO);
    draw_program->generated = 0;

    return draw_program;
}

void draw_program_free(draw_program_T* draw_program)
{
    draw_program_deletebuffers(draw_program);
    free(draw_program);
}
