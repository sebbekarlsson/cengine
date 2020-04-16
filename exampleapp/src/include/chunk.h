#ifndef EXAMPLEAPP_CHUNK_H
#define EXAMPLEAPP_CHUNK_H

enum
{
    BLOCK_STONE = 1
} block_type;

typedef struct CHUNK_STRUCT
{
    int blocks[16][16];
    int x;
    int y;
} chunk_T;

chunk_T* init_chunk(int x, int y);

void chunk_tick(chunk_T* chunk);

void chunk_draw(chunk_T* chunk);
#endif
