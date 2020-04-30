#ifndef APP_MAIN_ACTOR_H
#define APP_MAIN_ACTOR_H
#include <cengine/actor.h>


typedef struct MAIN_ACTOR_STRUCT
{
    actor_T base;
} main_actor_T;

main_actor_T* init_main_actor(float x, float y, float z);

void main_actor_tick(actor_T* self);

void main_actor_draw(actor_T* self);
#endif
