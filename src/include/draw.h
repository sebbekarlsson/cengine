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
    draw_options_T draw_options
);

void draw_line(
    draw_program_T* draw_program,
    draw_options_T draw_options
);
#endif
