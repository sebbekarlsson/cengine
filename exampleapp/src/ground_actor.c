#include "include/ground_actor.h"
#include <cengine/actor.h>
#include <cengine/application.h>
#include <cengine/draw.h>
#include <cengine/texture.h>
#include <cengine/keyboard.h>
#include <cengine/physics.h>


extern application_T* APP;


void ground_actor_draw(actor_T* self)
{
    draw_texture(
        self->VBO,
        self->EBO,
        APP->shader_program_default,
        self->texture,
        self->x, self->y, self->z,
        32,
        32,
        255,
        255,
        255,
        1.0f
    );
}

actor_T* init_ground_actor(float x, float y, float z)
{
    actor_T* actor = init_actor(x, y, z);
    actor->texture = texture_get("res/image/ground.png");
    actor->draw = ground_actor_draw;
    return actor;
}
