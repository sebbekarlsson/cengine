#ifndef CENGINE_ACTOR_H
#define CENGINE_ACTOR_H
typedef struct ACTOR_STRUCT
{
    unsigned int VBO;
    unsigned int EBO;
    unsigned int texture; 

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

actor_T* init_actor(unsigned int texture, float x, float y, float z);
#endif
