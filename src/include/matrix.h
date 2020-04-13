#ifndef CENGINE_MATRIX_H
#define CENGINE_MATRIX_H
#include <cglm/cglm.h>
#include <cglm/call.h>

void matrix_generate(
    float trans_x,
    float trans_y,
    float trans_z,
    float rot_x,
    float rot_y,
    float rot_z,
    float offset_x,
    float offset_y,
    float offset_z,
    unsigned int reverse,
    mat4 final
);
#endif
