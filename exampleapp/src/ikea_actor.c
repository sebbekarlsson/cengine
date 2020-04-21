#include "include/ikea_actor.h"
#include "include/ikea_scene.h"
#include <cengine/actor.h>
#include <cengine/application.h>
#include <cengine/draw.h>
#include <cengine/texture.h>
#include <cengine/keyboard.h>
#include <cengine/physics.h>
#include <math.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


extern application_T* APP;
extern texture_T* TEXTURE_CHARACTER_TILES;


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
    ikea_scene_T* ikea_scene = (ikea_scene_T*) scene;
    

    float next_x = (self->x + 8) + xa + (xa > 0 ? 8 : xa < 0 ? -8 : 0);
    float next_y = (self->y + 8) + ya + (ya > 0 ? 8 : ya < 0 ? -8 : 0);

    chunk_T* chunk = ikea_scene_get_chunk(ikea_scene, next_x, next_y); 

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            float bx = chunk->x + (x*32);
            float by = chunk->y + (y*32);

            int block = chunk->blocks[x][y];

            if (block == BLOCK_AIR)
                continue;

            if (self->x+16+xa > bx && self->x+xa < bx + w)
            {
                if (self->y+16+ya > by && self->y+ya < by + h)
                {
                    self->dy = 0;
                    
                    if (self->y+ya < by)
                        ((ikea_actor_T*)self)->ground = 1;

                    if ((self->y+16)-ya > by && self->y-ya < by+h)
                        self->dx = 0;

                    return;
                }
            }
        } 
    } 

    self->x += xa;
    self->y += ya;
    ((ikea_actor_T*)self)->ground = 0;
}

void ikea_actor_tick(actor_T* self)
{
    scene_T* scene = application_get_current_scene(APP);
    ikea_scene_T* ikea_scene = (ikea_scene_T*) scene;

    camera_set_x(scene->camera, self->x - (APP->width/2) + 16);
    camera_set_y(scene->camera, self->y - (APP->height/2) + 16);

    double dt = APP->delta_time;
    
    float v = 30.0f;
    self->friction = 20.9f;
    float air_res = 10.0f;
    float gravity = 22.0f * dt;

    physics_to_zero(&self->dx, self->friction);
    physics_to_zero(&self->dy, air_res);

    self->dy += gravity;
    
    int left_block = ikea_scene_get_block(ikea_scene, self->x-4, self->y+16);
    int right_block = ikea_scene_get_block(ikea_scene, self->x+16+4, self->y+16);

    if (
        left_block != BLOCK_AIR ||
        right_block != BLOCK_AIR
    )
    {
        ((ikea_actor_T*)self)->ground = 1;
    }
    
    // bounce away if moving to fast against wall 
    if (self->dx <= -0.7f)
    {
        if (left_block)
            physics_vec2_push(&self->dx, &self->dy, 0.0f, abs(self->dx)*2.0f);
    }

    // bounce away if moving to fast against wall 
    if (self->dx >= 0.7f)
    {
        if (right_block)
            physics_vec2_push(&self->dx, &self->dy, 180.0f, abs(self->dx)*2.0f);
    }
    
    if (keyboard_check_pressed(GLFW_KEY_RIGHT))
        physics_vec2_push(&self->dx, &self->dy, 0.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_LEFT))
        physics_vec2_push(&self->dx, &self->dy, 180.0f, v * dt);

    if (keyboard_check_pressed(GLFW_KEY_SPACE))
    {
        ikea_scene_set_block(ikea_scene, self->x, self->y+32, BLOCK_AIR);
    }

    // jump
    if (keyboard_check_pressed(GLFW_KEY_UP) &&  ((ikea_actor_T*)self)->ground)
    {
        float a = 90.0f;
        float f = 8.0f;
        
        if (left_block)
            a -= 36.0f;
        else
        if (right_block)
            a += 36.0f;

        if (left_block || right_block)
            f -= 4.0f;

        physics_vec2_push(&self->dx, &self->dy, a, f);
    }

    if (self->dx > 0)
    {
        self->sprite->flip_x = 0;
        self->sprite->animated = 1;
    }
    else
    if (self->dx < 0)
    {
        self->sprite->flip_x = 1;
        self->sprite->animated = 1;
    }
    else
    {
        self->sprite->animated = 0;
    }

    move(self, self->dx, self->dy); 
}

void ikea_actor_draw(actor_T* self)
{
    sprite_draw(self->sprite, self->VBO, self->EBO, APP->shader_program_default, self->x, self->y, self->z);

    glUseProgram(APP->shader_program_default);
    glUniform3fv(glGetUniformLocation(APP->shader_program_default, "light_pos"), 1, (float[]){self->x, self->y, self->z});
}

ikea_actor_T* init_ikea_actor(float x, float y, float z)
{
    ikea_actor_T* ikea_actor = calloc(1, sizeof(struct IKEA_ACTOR_STRUCT));
    actor_T* actor = actor_constructor((actor_T*) ikea_actor, x, y, z);
    actor->tick = ikea_actor_tick;
    actor->draw = ikea_actor_draw;
    ikea_actor->ground = 0;
    
    actor->sprite = init_sprite();
    actor->sprite->delay = 0.2f;
    
    for (int i = 0; i < 6; i++)
    {
        texture_T* texture = init_texture(TEXTURE_CHARACTER_TILES->id, TEXTURE_CHARACTER_TILES->width, TEXTURE_CHARACTER_TILES->height);
        texture->atlas_width = 6;
        texture->atlas_height = 11;
        texture->shift_x = 4;
        texture->shift_y = i;
        texture->width = 16;
        texture->height = 16;

        sprite_add_texture(actor->sprite, texture);
    }

    return ikea_actor;
}
