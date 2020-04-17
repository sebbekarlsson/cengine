#ifndef EXAMPLEAPP_CHUNK_H
#define EXAMPLEAPP_CHUNK_H

#define CHUNK_SIZE 16
#define BLOCK_SIZE 32

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
    BIOME_SPACE
} biome_type;

typedef struct CHUNK_STRUCT
{
    int blocks[CHUNK_SIZE][CHUNK_SIZE];
    int x;
    int y;
} chunk_T;

chunk_T* init_chunk(int x, int y);

void chunk_tick(chunk_T* chunk);

void chunk_draw(chunk_T* chunk);
#endif
