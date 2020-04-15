#ifndef EXAMPLEAPP_IKEA_ACTOR_H
#define EXAMPLEAPP_IKEA_ACTOR_H
#include <cengine/actor.h>


typedef struct IKEA_ACTOR_STRUCT
{
    actor_T base;
    unsigned int ground;
} ikea_actor_T;

ikea_actor_T* init_ikea_actor(float x, float y, float z);
#endif
