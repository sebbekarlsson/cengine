#include "include/actor.h"
#include "include/application.h"
#include <stdlib.h>
#include <GL/glew.h>


extern application_T* APP;


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

    actor->rx = 0;
    actor->ry = 0;
    actor->rz = 0;

    actor->friction = 0;

    actor->hitbox_width = 16;
    actor->hitbox_height = 16;
    actor->hitbox_depth = 16;

    actor->tick = (void*) 0;
    actor->draw = (void*) 0;

    actor->draw_program = init_draw_program(APP->shader_program_color);

    return actor;
}

void actor_draw_default(actor_T* actor)
{
    scene_T* scene = application_get_current_scene(APP);

    if (APP->debug_mode)
    {
        draw_line(
            actor->draw_program,
            actor->x, actor->y, actor->z,
            actor->x + actor->hitbox_width, actor->y, actor->z,
            255, 0, 0, 1.0f 
        );

        draw_line(
            actor->draw_program,
            actor->x, actor->y, actor->z,
            actor->x, actor->y + actor->hitbox_height, actor->z,
            255, 0, 0, 1.0f 
        );
    }

    if (actor->sprite)
    {
        sprite_draw(
            actor->sprite,
            actor->x,
            actor->y,
            actor->z
        );
    }
}
