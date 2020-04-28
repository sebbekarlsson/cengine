#include "include/chunk.h"
#include <cengine/draw.h>
#include <cengine/application.h>
#include <stdlib.h>
#include <sys/param.h>

extern unsigned int TEXTURE_TILES;
extern application_T* APP;


chunk_T* init_chunk(int x, int y)
{
    chunk_T* chunk = calloc(1, sizeof(struct CHUNK_STRUCT));
    chunk->x = x;
    chunk->y = y;

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
            chunk->blocks[i][j] = 0;
    }

    chunk->draw_program = init_draw_program(APP->shader_program_default);

    return chunk;
}

void chunk_tick(chunk_T* chunk)
{ 
}

void chunk_draw(chunk_T* chunk)
{
    scene_T* scene = application_get_current_scene(APP);


    for (int x = 0; x < 16; x++)
    {
        for (int y = 0; y < 16; y++)
        {
            int block = chunk->blocks[x][y];

            if (block == BLOCK_AIR)
                continue;
            
            int tex_x = 0;
            int tex_y = 0;
        
            if (block == BLOCK_HOTSTONE)
            {
                tex_x = 0;
                tex_y = 0;
            }
            else
            if (block == BLOCK_GRASS)
            {
                tex_x = 1;
                tex_y = 0;
            }
            else
            if (block == BLOCK_STONE)
            {
                tex_x = 0;
                tex_y = 1;
            }
            else
            if (block == BLOCK_MOONROCK)
            {
                tex_x = 1;
                tex_y = 1;
            }

            glBindVertexArray(scene->VAO);

            draw_texture(
                chunk->draw_program,
                TEXTURE_TILES,
                chunk->x + (x*32), chunk->y + (y*32), 0,
                BLOCK_SIZE,
                BLOCK_SIZE,
                255,
                255,
                255,
                1.0f,
                tex_x,
                tex_y,
                32,
                32,
                0,
                0
            );
        }
    }
}
