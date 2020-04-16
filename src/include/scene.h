#ifndef CENGINE_SCENE_H
#define CENGINE_SCENE_H
#include "dynamic_list.h"
#include "actor.h"
#include "camera.h"


typedef struct SCENE_STRUCT
{
    dynamic_list_T* actors;

    unsigned int VAO; 

    void (*tick)(struct SCENE_STRUCT* self);
    void (*draw)(struct SCENE_STRUCT* self);

    camera_T* camera;
} scene_T;

scene_T* init_scene();

scene_T* scene_constructor(scene_T* scene);

void scene_tick(scene_T* scene);

void scene_draw(scene_T* scene);

void scene_add_actor(scene_T* scene, actor_T* actor);
#endif
