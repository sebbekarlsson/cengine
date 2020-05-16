#include "include/ikea_scene.h"
#include "include/ikea_actor.h"
#include "include/perlin.h"
#include <cengine/texture.h>
#include <cengine/window.h>
#include <cengine/draw.h>
#include <cengine/application.h>
#include <sys/param.h>


extern application_T* APP;


void ikea_scene_tick(scene_T* scene)
{
    ikea_scene_T* ikea_scene = (ikea_scene_T*) scene;
    
    actor_T* actor_camera = (actor_T*) scene->camera;

    for (int x = 0; x < NR_CHUNKS; x++)
    {
        for (int y = 0; y < NR_CHUNKS; y++)
        {
            chunk_T* chunk = ikea_scene->chunks[x][y];

            if (
                chunk->x + (CHUNK_SIZE*32) < actor_camera->x ||
                chunk->x > actor_camera->x + RES_WIDTH ||

                chunk->y > actor_camera->y + RES_HEIGHT ||
                chunk->y + (CHUNK_SIZE*32) < actor_camera->y
            )
                continue;

            chunk_tick(ikea_scene->chunks[x][y]);
        }
    } 
}

void ikea_scene_draw(scene_T* scene)
{
    ikea_scene_T* ikea_scene = (ikea_scene_T*) scene;

    actor_T* actor_camera = (actor_T*) scene->camera;

    camera_bind(scene->camera);

    for (int x = 0; x < NR_CHUNKS; x++)
    {
        for (int y = 0; y < NR_CHUNKS; y++)
        {
            chunk_T* chunk = ikea_scene->chunks[x][y];

            if (
                chunk->x + (CHUNK_SIZE*32) < actor_camera->x ||
                chunk->x > actor_camera->x + RES_WIDTH ||

                chunk->y > actor_camera->y + RES_HEIGHT ||
                chunk->y + (CHUNK_SIZE*32) < actor_camera->y
            )
                continue;

            chunk_draw(chunk);
        }
    }

    camera_unbind(scene->camera);

    glBindVertexArray(scene->VAO);

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 0);

    draw_options_T draw_options = DRAW_OPTIONS_INIT;
    draw_options.font_size = 24;
    draw_options.text = "hello";
    draw_options.x = 128;
    draw_options.y = 128;
    draw_options.z = 1;
    draw_options.r = 255;
    draw_options.g = 255;
    draw_options.b = 255;
    draw_options.fontpath = "/usr/share/fonts/truetype/crosextra/Carlito-Regular.ttf";

    draw_text(scene->draw_program_text, draw_options);

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 1);
}

static int mod(int x, int N)
{
    return (x % N + N) %N;
}

void ikea_scene_set_block(ikea_scene_T* ikea_scene, float x, float y, int type)
{
    chunk_T* chunk = ikea_scene_get_chunk(ikea_scene, x, y);

    int bx = mod(x/32, CHUNK_SIZE);
    int by = mod(y/32, CHUNK_SIZE);

    chunk->blocks[MIN(CHUNK_SIZE, bx)][MIN(CHUNK_SIZE, by)] = type;
}

int ikea_scene_get_block(ikea_scene_T* ikea_scene, float x, float y)
{
    chunk_T* chunk = ikea_scene_get_chunk(ikea_scene, x, y);

    int bx = mod(x/32, CHUNK_SIZE);
    int by = mod(y/32, CHUNK_SIZE);

    return chunk->blocks[MIN(CHUNK_SIZE, bx)][MIN(CHUNK_SIZE, by)];
}

ikea_scene_T* init_ikea_scene()
{
    ikea_scene_T* ikea_scene = calloc(1, sizeof(struct IKEA_SCENE_STRUCT));
    scene_T* scene = scene_constructor((scene_T*)ikea_scene);
    scene->draw = ikea_scene_draw;
    scene->tick = ikea_scene_tick;

    for (int x = 0; x < NR_CHUNKS; x++)
        for (int y = 0; y < NR_CHUNKS; y++)
            ikea_scene->chunks[x][y] = init_chunk(x*32*CHUNK_SIZE, y*32*CHUNK_SIZE);

    actor_T* player = scene_add_actor(scene, (actor_T*)init_ikea_actor(0, 0, 2));
    unsigned int player_placed = 0;

    for (int x = 0; x < CHUNK_SIZE*NR_CHUNKS; x++)
    {
        int h = ((int)(perlin_get2d(x*BLOCK_SIZE, 0, 0.0005f, 10.0f, 13882) * 64));

        for (int y = CHUNK_SIZE*NR_CHUNKS; y > h; y--)
        {
            unsigned int block = ((int)(perlin_get2d(x*BLOCK_SIZE, y*BLOCK_SIZE, 0.005f, 10.0f, 23882) * NR_BLOCKS));

            if (y <= h + ((int)(perlin_get2d(x*BLOCK_SIZE, y*BLOCK_SIZE, 0.005f, 10.0f, 13382) * 5)))
                block = BLOCK_GRASS;

            ikea_scene_set_block(ikea_scene, x*BLOCK_SIZE, y*BLOCK_SIZE, block);

            if (block && y <= h)
            {
                if (!player_placed)
                {
                    printf("player placed\n");
                    player->x = (x+1)*32;
                    player->y = (y-16)*32;
                    player_placed = 1;
                }
            }
        }
    }

    return ikea_scene;
}

chunk_T* ikea_scene_get_chunk(ikea_scene_T* ikea_scene, float x, float y)
{
    int chunk_x = x / (32*CHUNK_SIZE);
    int chunk_y = y / (32*CHUNK_SIZE);

    return ikea_scene->chunks[MIN(NR_CHUNKS-1, MAX(0, chunk_x))][MIN(NR_CHUNKS-1, MAX(0, chunk_y))];
}
