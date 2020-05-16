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

    glBindVertexArray(scene->VAO);

    draw_options_T draw_options_line = DRAW_OPTIONS_INIT;
    draw_options_line.x = chunk->x;
    draw_options_line.y = chunk->y;
    draw_options_line.z = 0;
    draw_options_line.endx = chunk->x + CHUNK_SIZE * BLOCK_SIZE;
    draw_options_line.endy = chunk->y;
    draw_options_line.r = 255;

    draw_line(
        scene->draw_program_color,
        draw_options_line
    );

    draw_options_line.x = chunk->x;
    draw_options_line.y = chunk->y;
    draw_options_line.z = 0;
    draw_options_line.endx = chunk->x;
    draw_options_line.endy = chunk->y + CHUNK_SIZE * BLOCK_SIZE;
    draw_options_line.r = 0;
    draw_options_line.g = 255;

    draw_line(
        scene->draw_program_color,
        draw_options_line
    );

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

            draw_options_T draw_options = DRAW_OPTIONS_INIT;
            draw_options.texture = TEXTURE_TILES;
            draw_options.x = chunk->x + (x*32);
            draw_options.y = chunk->y + (y*32);
            draw_options.width = BLOCK_SIZE;
            draw_options.height = BLOCK_SIZE;
            draw_options.r = 255;
            draw_options.g = 255;
            draw_options.b = 255;
            draw_options.shift_x = tex_x;
            draw_options.shift_y = tex_y;
            draw_options.atlas_width = 32;
            draw_options.atlas_height = 32;

            draw_texture(
                chunk->draw_program,
                draw_options
            );
        }
    }
}
