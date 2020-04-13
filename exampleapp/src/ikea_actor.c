#include "include/ikea_actor.h"
#include <cengine/actor.h>
#include <cengine/application.h>
#include <cengine/draw.h>
#include <cengine/texture.h>
#include <cengine/keyboard.h>
#include <cengine/physics.h>


extern application_T* APP;


void ikea_actor_tick(actor_T* self)
{
    double dt = APP->delta_time;
    
    float v = 80.0f;
    self->friction = 20.9f;

    if (keyboard_check_pressed(GLFW_KEY_RIGHT))
        physics_vec2_push(&self->dx, &self->dy, 0.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_LEFT))
        physics_vec2_push(&self->dx, &self->dy, 180.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_UP))
        physics_vec2_push(&self->dx, &self->dy, 90.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_DOWN))
        physics_vec2_push(&self->dx, &self->dy, 270.0f, v * dt);
}

void ikea_actor_draw(actor_T* self)
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

actor_T* init_ikea_actor(float x, float y, float z)
{
    actor_T* actor = init_actor(x, y, z);
    actor->texture = texture_get("res/image/ikea.png");
    actor->tick = ikea_actor_tick;
    actor->draw = ikea_actor_draw;
    return actor;
}
