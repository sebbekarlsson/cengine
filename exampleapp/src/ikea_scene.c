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
                chunk->x > actor_camera->x + APP->width ||

                chunk->y > actor_camera->y + APP->height ||
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
                chunk->x > actor_camera->x + APP->width ||

                chunk->y > actor_camera->y + APP->height ||
                chunk->y + (CHUNK_SIZE*32) < actor_camera->y
            )
                continue;

            chunk_draw(chunk);
        }
    }

    camera_unbind(scene->camera);

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

    actor_T* player = scene_add_actor(scene, (actor_T*)init_ikea_actor(0, 0, 0));
    unsigned int player_placed = 0;

    for (int i = 0; i < CHUNK_SIZE*NR_CHUNKS; i++)
    {
        float h = CHUNK_SIZE*NR_CHUNKS;//_round(perlin_get2d(i, 0, 0.006f, 20.0f) * 100);

        for (int y = 0; y < h; y++)
        {
            float cave_freq = 0.006f;
            float cave_depth = 20.0f;
            int block_type = BLOCK_STONE;

            int bio = ((y*32) / ((NR_CHUNKS*CHUNK_SIZE*BLOCK_SIZE) / NR_BIOMES));

           
            if (bio == BIOME_SPACE)
            {
                int nr_blocks = 2;
                cave_freq += 0.4f;
                cave_depth += 0.9f;

                int b = (int)(perlin_get2d(i, y, 0.06, 20.0f, 1233) * nr_blocks);

                switch (b)
                {
                    case 0: block_type = BLOCK_STONE; break;
                    case 1: block_type = BLOCK_MOONROCK; break;
                }
            }
            else
            if (bio == BIOME_WORLD)
            {
                int nr_blocks = 2;

                int b = (int)(perlin_get2d(i, y, 0.06, 20.0f, 1233) * nr_blocks);

                switch (b)
                {
                    case 0: block_type = BLOCK_STONE; break;
                    case 1: block_type = BLOCK_GRASS; break;
                }
            }
            else
            if (bio == BIOME_HELL)
            {
                int nr_blocks = 2;

                int b = (int)(perlin_get2d(i, y, 0.06, 20.0f, 1233) * nr_blocks);

                switch (b)
                {
                    case 0: block_type = BLOCK_STONE; break;
                    case 1: block_type = BLOCK_HOTSTONE; break;
                }
            }

            float p = perlin_get2d(i, y, cave_freq, cave_depth, 93819);

            if (p >= 0.55f)
                block_type = BLOCK_AIR;

            int yy = (CHUNK_SIZE*NR_CHUNKS) - y;

            ikea_scene_set_block(ikea_scene, i*32, yy*32, block_type);

            // place player on top of first block
            if (y >= h-1 && !player_placed && block_type != BLOCK_AIR)
            {
                player->x = i*32;
                player->y = ((yy-2)*32);
                player_placed = 1;
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
