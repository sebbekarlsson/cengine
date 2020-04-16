#include "include/actor.h"
#include <stdlib.h>
#include <GL/glew.h>


actor_T* init_actor(float x, float y, float z)
{
    actor_T* actor = calloc(1, sizeof(struct ACTOR_STRUCT));
    return actor_constructor(actor, x, y, z);
}

actor_T* actor_constructor(actor_T* actor, float x, float y, float z)
{
    actor->sprite = (void*)0;

    glGenBuffers(1, &actor->VBO);
    glGenBuffers(1, &actor->EBO); 

    actor->x = x;
    actor->y = y;
    actor->z = z;

    actor->dx = 0;
    actor->dy = 0;
    actor->dz = 0;

    actor->friction = 0;

    actor->tick = (void*) 0;
    actor->draw = (void*) 0;

    return actor;
}
