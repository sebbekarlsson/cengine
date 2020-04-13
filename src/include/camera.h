#ifndef CENGINE_CAMERA_H
#define CENGINE_CAMERA_H
#include "actor.h"


typedef struct CAMERA_STRUCT
{
    actor_T base;
} camera_T;

camera_T* init_camera(float x, float y, float z);
#endif
