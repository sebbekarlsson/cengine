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
extern unsigned int TEXTURE_CHARACTER_TILES;


static int mod(int x, int N)
{
    return (x % N + N) %N;
}

static float angle(float x1, float y1, float x2, float y2)
{
    float xDiff = x2 - x1;
    float yDiff = y2 - y1;
    return atan2(yDiff, xDiff) * 180.0 / GLM_PI;
}

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

    chunk_T* chunk = ikea_scene_get_chunk(ikea_scene, (next_x)/(32*16), (next_y)/(32*16));

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            float bx = chunk->x + (x*32);
            float by = chunk->y + (y*32);

            int block = chunk->blocks[x][y];

            if (block != BLOCK_STONE)
                continue;

            if (self->x+16+xa > bx && self->x+xa < bx + w)
            {
                if (self->y+16+ya > by && self->y+ya < by + h)
                {
                    self->dy = 0;
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

    camera_set_x(scene->camera, self->x - (APP->width/2) + 16);
    camera_set_y(scene->camera, self->y - (APP->height/2) + 16);

    double dt = APP->delta_time;
    
    float v = 80.0f;
    self->friction = 20.9f;
    float air_res = 10.0f;
    float gravity = 22.0f * dt;

    physics_to_zero(&self->dx, self->friction);
    physics_to_zero(&self->dy, air_res);

    self->dy += gravity;
    
    if (keyboard_check_pressed(GLFW_KEY_RIGHT))
        physics_vec2_push(&self->dx, &self->dy, 0.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_LEFT))
        physics_vec2_push(&self->dx, &self->dy, 180.0f, v * dt);
    if (keyboard_check_pressed(GLFW_KEY_UP) &&  ((ikea_actor_T*)self)->ground)
        physics_vec2_push(&self->dx, &self->dy, 90.0f, 8.0f);
    if (keyboard_check_pressed(GLFW_KEY_DOWN))
        physics_vec2_push(&self->dx, &self->dy, 270.0f, v * dt);


    move(self, self->dx, self->dy); 
}

void ikea_actor_draw(actor_T* self)
{
    draw_texture(
        self->VBO,
        self->EBO,
        APP->shader_program_default,
        TEXTURE_CHARACTER_TILES,
        self->x, self->y, self->z,
        16,
        16,
        255,
        255,
        255,
        1.0f,
        4,
        0,
        6,
        11
    );

    glUseProgram(APP->shader_program_default);
    glUniform3fv(glGetUniformLocation(APP->shader_program_default, "light_pos"), 1, (float[]){self->x, self->y, self->z});
}

ikea_actor_T* init_ikea_actor(float x, float y, float z)
{
    ikea_actor_T* ikea_actor = calloc(1, sizeof(struct IKEA_ACTOR_STRUCT));
    actor_T* actor = actor_constructor((actor_T*) ikea_actor, x, y, z);
    actor->texture = texture_get("res/image/ikea.png");
    actor->tick = ikea_actor_tick;
    actor->draw = ikea_actor_draw;
    ikea_actor->ground = 0;

    return ikea_actor;
}
