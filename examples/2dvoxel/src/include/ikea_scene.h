#ifndef VOXEL2D_IKEA_SCENE_H
#define VOXEL2D_IKEA_SCENE_H
#include <cengine/scene.h>
#include "chunk.h"

#define NR_CHUNKS 64

typedef struct IKEA_SCENE_STRUCT
{
    scene_T base;
    chunk_T* chunks[NR_CHUNKS][NR_CHUNKS];
} ikea_scene_T;


ikea_scene_T* init_ikea_scene();

chunk_T* ikea_scene_get_chunk(ikea_scene_T* ikea_scene, float x, float y);

int ikea_scene_get_block(ikea_scene_T* ikea_scene, float x, float y);

void ikea_scene_set_block(ikea_scene_T* ikea_scene, float x, float y, int type);
#endif
