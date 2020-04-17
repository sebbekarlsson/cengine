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
            int block_top = chunk->blocks[x][MAX(0,y-1)];
            int block_right = chunk->blocks[MIN(16-1, x+1)][y];
            int block_top_right = chunk->blocks[MIN(16-1, x+1)][MAX(0,y-1)];
            int block_top_left = chunk->blocks[MAX(0, x-1)][MAX(0,y-1)];

            if (block == 0)
                continue;

            int tex_x = 0;
            int tex_y = 2;

            if (block_top == BLOCK_STONE)
                tex_x = 1;

            if (block_top != BLOCK_STONE && (block_top_right == BLOCK_STONE || block_top_left == BLOCK_STONE))
            {
                tex_y = 1;
                tex_x = 7;
            }

            glBindVertexArray(scene->VAO);

            unsigned int VBO;
            unsigned int EBO;
            
            glGenBuffers(1, &VBO);
            glGenBuffers(1, &EBO);

            draw_texture(
                VBO,
                EBO,
                APP->shader_program_default,
                TEXTURE_TILES,
                chunk->x + (x*32), chunk->y + (y*32), 0,
                32,
                32,
                255,
                255,
                255,
                1.0f,
                tex_x,
                tex_y,
                8,
                5,
                0,
                0
            );

            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO); 
        }
    }
}
