#ifndef CENGINE_CAMERA_H
#define CENGINE_CAMERA_H
#include "actor.h"
#include <cglm/cglm.h>
#include <cglm/call.h>


typedef struct CAMERA_STRUCT
{
    actor_T base;

    mat4 view;

    float offset_x;
    float offset_y;
    float offset_z;

    unsigned int reverse;
} camera_T;

camera_T* init_camera(float x, float y, float z);

void camera_bind(camera_T* camera);

void camera_unbind(camera_T* camera);

void camera_send_view_to_shader(camera_T* camera, unsigned int shader_program);
#endif
