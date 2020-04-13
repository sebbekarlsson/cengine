#ifndef CENGINE_ACTOR_H
#define CENGINE_ACTOR_H
typedef struct ACTOR_STRUCT
{
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture;

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

    void (*tick)(struct ACTOR_STRUCT* self);
    void (*draw)(struct ACTOR_STRUCT* self);
} actor_T;

actor_T* init_actor(float x, float y, float z);

actor_T* actor_constructor(actor_T* actor, float x, float y, float z);
#endif
