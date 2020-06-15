#ifndef CENGINE_SCENE_H
#define CENGINE_SCENE_H
#include "dynamic_list.h"
#include "actor.h"
#include "camera.h"
#include "draw.h"


typedef struct SCENE_STRUCT
{
    dynamic_list_T* actors;

    unsigned int VAO; 

    void (*tick)(struct SCENE_STRUCT* self);
    void (*draw)(struct SCENE_STRUCT* self);
    void (*pre_draw)(struct SCENE_STRUCT* self);
    void (*free)(struct SCENE_STRUCT* self);

    camera_T* camera;

    draw_program_T* draw_program;
    draw_program_T* draw_program_text;
    draw_program_T* draw_program_color;

    float r;
    float g;
    float b;

    unsigned int paused;
} scene_T;

scene_T* init_scene();

scene_T* scene_constructor(scene_T* scene);

void scene_free(scene_T* scene);

void scene_tick(scene_T* scene);

void scene_draw(scene_T* scene);

actor_T* scene_add_actor(scene_T* scene, actor_T* actor);

void scene_remove_actor(scene_T* scene, actor_T* actor);
#endif
