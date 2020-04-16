#include "include/ikea_scene.h"
#include "include/ikea_actor.h"
#include "include/ground_actor.h"
#include "include/perlin.h"
#include <cengine/texture.h>
#include <cengine/window.h>
#include <cengine/draw.h>
#include <cengine/application.h>
#include <sys/param.h>


extern application_T* APP;

extern volatile int SEED;


void ikea_scene_tick(scene_T* scene)
{
    ikea_scene_T* ikea_scene = (ikea_scene_T*) scene;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            chunk_tick(ikea_scene->chunks[x][y]);
        }
    } 
}

void ikea_scene_draw(scene_T* scene)
{
    ikea_scene_T* ikea_scene = (ikea_scene_T*) scene;

    camera_bind(scene->camera);

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            chunk_draw(ikea_scene->chunks[x][y]);
        }
    }

    camera_unbind(scene->camera);

    unsigned int VBO;
    unsigned int EBO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    double mx = window_mouse_get_x();
    double my = window_mouse_get_y();

    texture_T* texture = texture_get("res/image/potato.png");

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 0);

    draw_texture(
        VBO,
        EBO,
        APP->shader_program_default,
        texture->id,
        mx, my, 0,
        32,
        32,
        255,
        255,
        255,
        1.0f,
        0,
        0,
        0,
        0
    );

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    texture_free(texture);

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 1);
}

static int _round(float num)
{
    return (int)(num < 0 ? (num - 0.5) : (num + 0.5));
}

static int mod(int x, int N)
{
    return (x % N + N) %N;
}

ikea_scene_T* init_ikea_scene()
{
    SEED = 11111;
    ikea_scene_T* ikea_scene = calloc(1, sizeof(struct IKEA_SCENE_STRUCT));
    scene_T* scene = scene_constructor((scene_T*)ikea_scene);
    scene->draw = ikea_scene_draw;
    scene->tick = ikea_scene_tick;

    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            ikea_scene->chunks[x][y] = init_chunk(x*32*16, y*32*16);
        }
    }

    scene_add_actor(scene, (actor_T*)init_ikea_actor(0, 0, 0));

    for (int i = 0; i < 128; i++)
    {
        float h = _round(perlin_get2d(i, 0, 0.1f, 20.0f) * 12);

        for (int y = h; y > 0; y--)
        {
            int chunk_x = i / 16;
            int chunk_y = -(y) / 16;
            int bx = mod(i, 16);
            int by = mod(-(y), 16);

            //printf("chunk_x: %d, chunk_y: %d, bx: %d, by: %d\n", chunk_x, chunk_y, bx, by);

            ikea_scene->chunks[MIN(16-1, MAX(0, chunk_x))][MIN(16-1, MAX(0, chunk_y))]->blocks[MIN(16, bx)][MIN(16, by)] = BLOCK_STONE;
        }
    }

    return ikea_scene;
}

chunk_T* ikea_scene_get_chunk(ikea_scene_T* ikea_scene, float x, float y)
{
    int chunk_x = mod(x, 16);
    int chunk_y = mod(y, 16);
    return ikea_scene->chunks[MIN(16-1, MAX(0, chunk_x))][MIN(16-1, MAX(0, chunk_y))];
}
