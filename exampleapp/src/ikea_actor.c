#include "include/ikea_actor.h"
#include <cengine/actor.h>
#include <cengine/application.h>
#include <cengine/draw.h>
#include <cengine/texture.h>
#include <cengine/keyboard.h>
#include <cengine/physics.h>


extern application_T* APP;


static void move(actor_T* self, float xa, float ya)
{
    if (xa != 0 && ya != 0)
    {
        move(self, xa, 0);
        move(self, 0, ya);
        return;
    }

    float w = 32;
    float h = 32;

    scene_T* scene = application_get_current_scene(APP);

    for (int i = 0; i < scene->actors->size; i++)
    {
        actor_T* other = scene->actors->items[i];

        if (other == self)
            continue;

        if (self->x+w+xa > other->x && self->x+xa < other->x + w)
        {
            if (self->y+h+ya > other->y && self->y+ya < other->y + h)
            {
                self->dy = 0;

                if ((self->y+h)-ya > other->y && self->y-ya < other->y+h)
                    self->dx = 0;

                return;
            }
        } 
    } 

    self->x += xa;
    self->y += ya;
}

void ikea_actor_tick(actor_T* self)
{
    scene_T* scene = application_get_current_scene(APP);

    camera_set_x(scene->camera, self->x - (APP->width/2) + 16);
    camera_set_y(scene->camera, self->y - (APP->height/2) + 16);

    double dt = APP->delta_time;
    
    float v = 80.0f;
    self->friction = 20.9f;
    
    if (keyboard_check_pressed(GLFW_KEY_RIGHT))
        physics_vec2_push(&self->dx, &self->dy, 0.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_LEFT))
        physics_vec2_push(&self->dx, &self->dy, 180.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_UP))
        physics_vec2_push(&self->dx, &self->dy, 90.0f, (v + 60.0f) * dt);
    if (keyboard_check_pressed(GLFW_KEY_DOWN))
        physics_vec2_push(&self->dx, &self->dy, 270.0f, v * dt);

    float gravity = 32.0f * dt;

    self->dy += gravity;

    move(self, self->dx, self->dy);
    physics_to_zero(&self->dx, self->friction);
    physics_to_zero(&self->dy, self->friction);

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
