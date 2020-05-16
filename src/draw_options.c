#include "include/draw_options.h"
#include "include/matrix.h"


void draw_options_get_matrix(draw_options_T draw_options, mat4 dest)
{
    matrix_generate(
        draw_options.x,
        draw_options.y,
        draw_options.z,
        draw_options.rx,
        draw_options.ry,
        draw_options.rz,
        draw_options.offset_x,
        draw_options.offset_y,
        draw_options.offset_z,
        draw_options.reverse,
        dest
    );
}
