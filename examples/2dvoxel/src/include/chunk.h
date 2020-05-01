#ifndef VOXEL2D_CHUNK_H
#define VOXEL2D_CHUNK_H
#include <cengine/draw.h>

#define CHUNK_SIZE 16
#define BLOCK_SIZE 32

#define NR_BLOCKS 5
enum
{
    BLOCK_AIR = 0,
    BLOCK_HOTSTONE,
    BLOCK_STONE,
    BLOCK_GRASS,
    BLOCK_MOONROCK
} block_type;

#define NR_BIOMES 3
enum
{
    BIOME_HELL,
    BIOME_WORLD,
    BIOME_MOON
} biome_type;

typedef struct CHUNK_STRUCT
{
    int blocks[CHUNK_SIZE][CHUNK_SIZE];
    int x;
    int y;
    draw_program_T* draw_program;
} chunk_T;

chunk_T* init_chunk(int x, int y);

void chunk_tick(chunk_T* chunk);

void chunk_draw(chunk_T* chunk);
#endif
