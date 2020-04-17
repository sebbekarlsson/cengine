#ifndef EXAMPLEAPP_CHUNK_H
#define EXAMPLEAPP_CHUNK_H

#define CHUNK_SIZE 16

enum
{
    BLOCK_AIR,
    BLOCK_STONE
} block_type;

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
