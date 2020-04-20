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

    unsigned int VBO;
    unsigned int EBO;
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(scene->VAO);

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 0);
    draw_text(scene->VAO, VBO, EBO, APP->shader_program_default, "hello", "/usr/share/fonts/truetype/lato/Lato-Black.ttf", 8, 42, 0, 16, 255, 255, 255);

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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

static void ikea_scene_generate_planet(ikea_scene_T* ikea_scene, float x, float y, int biome)
{
    int planet_width = (int)(perlin_get2d(x, y, 0.006, 20.0f, 34887) * 32);

    int center_x = planet_width/2;
    int center_y = planet_width/2;

    int block_seed = 923819;

    for (int xx = center_x-(planet_width/2); xx < center_x+(planet_width/2); xx++)
    {
        for (int yy = center_x-(planet_width/2); yy < center_y+(planet_width/2); yy++)
        {
            if (hypot(xx - center_x, yy - center_y) < planet_width/2)
            {
                int b_x = (xx*32) + x;
                int b_y = (yy*32) + y;

                int block_type = BLOCK_STONE;

                if (biome == BIOME_HELL)
                {
                    int b = (int)(perlin_get2d(b_x, b_y, 0.006, 20.0f, block_seed)*2);

                    switch (b)
                    {
                        case 0: block_type = BLOCK_STONE; break;
                        case 1: block_type = BLOCK_HOTSTONE; break;
                    }
                }
                else
                if (biome == BIOME_WORLD)
                {
                    int b = (int)(perlin_get2d(b_x, b_y, 0.006, 20.0f, block_seed)*2);

                    switch (b)
                    {
                        case 0: block_type = BLOCK_STONE; break;
                        case 1: block_type = BLOCK_GRASS; break;
                    }
                }
                else
                if (biome == BIOME_MOON)
                {
                    int b = (int)(perlin_get2d(b_x, b_y, 0.006, 20.0f, block_seed)*2);

                    switch (b)
                    {
                        case 0: block_type = BLOCK_STONE; break;
                        case 1: block_type = BLOCK_MOONROCK; break;
                    }
                }

                ikea_scene_set_block(ikea_scene, b_x, b_y, block_type);
            }
        }
    }
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

    int planet_map_seed = 488837;
    float planet_map_freq = 0.6f;
    float planet_map_depth = 20.0f;

    int planet_type_seed = 643482;
    float planet_type_freq = 0.06;
    float planet_type_depth = 20.0f;
    
    for (int x = 0; x < CHUNK_SIZE*NR_CHUNKS; x++)
    {
        float h = CHUNK_SIZE*NR_CHUNKS;

        for (int y = 0; y < h; y++)
        {
            unsigned int should_generate_planet = ((int)(perlin_get2d(x*32, y*32, planet_map_freq, planet_map_depth, planet_map_seed) * 5)) == 0;


            if (should_generate_planet)
            {
                int biome_type = (int)(perlin_get2d(x*32, y*32, planet_type_freq, planet_type_depth, planet_type_seed) * NR_BIOMES);
                ikea_scene_generate_planet(ikea_scene, x*32, y*32, biome_type);

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
