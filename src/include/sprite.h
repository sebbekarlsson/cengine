#ifndef CENGINE_SPRITE_H
#define CENGINE_SPRITE_H
#include "dynamic_list.h"
#include "texture.h"


typedef struct SPRITE_STRUCT
{
    dynamic_list_T* textures;
    unsigned int index;
} sprite_T;

sprite_T* init_sprite();

sprite_T* init_sprite_with_texture(texture_T* texture);

void sprite_add_texture(sprite_T* sprite, texture_T* texture);

texture_T* sprite_get_current_texture(sprite_T* sprite);
#endif
