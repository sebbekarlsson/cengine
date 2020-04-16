#ifndef EXAMPLEAPP_IKEA_SCENE_H
#define EXAMPLEAPP_IKEA_SCENE_H
#include <cengine/scene.h>
#include "chunk.h"

typedef struct IKEA_SCENE_STRUCT
{
    scene_T base;
    chunk_T* chunks[16][16];
} ikea_scene_T;


ikea_scene_T* init_ikea_scene();

chunk_T* ikea_scene_get_chunk(ikea_scene_T* ikea_scene, float x, float y);
#endif
