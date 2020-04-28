#ifndef CENGINE_ACTOR_H
#define CENGINE_ACTOR_H
#include "sprite.h"

typedef struct ACTOR_STRUCT
{
    unsigned int VBO;
    unsigned int EBO;

    sprite_T* sprite;

    float rx;
    float ry;
    float rz;

    float x;
    float y;
    float z;

    float dx;
    float dy;
    float dz;

    float friction;

    float hitbox_width;
    float hitbox_height;
    float hitbox_depth;

    void (*tick)(struct ACTOR_STRUCT* self);
    void (*draw)(struct ACTOR_STRUCT* self);

    draw_program_T* draw_program;
} actor_T;

actor_T* init_actor(float x, float y, float z);

actor_T* actor_constructor(actor_T* actor, float x, float y, float z);

void actor_draw_default(actor_T* actor);
#endif
