#ifndef CENGINE_SPRITE_H
#define CENGINE_SPRITE_H
#include "dynamic_list.h"
#include "texture.h"

typedef struct SPRITE_STRUCT
{
    dynamic_list_T* textures;
    dynamic_list_T* texture_coords;
    unsigned int index;
    unsigned int coord_index;
} sprite_T;

sprite_T* init_sprite();

sprite_T* init_sprite_with_texture(texture_T* texture);

void sprite_add_texture(sprite_T* sprite, texture_T* texture);

texture_T* sprite_get_current_texture(sprite_T* sprite);

texture_coords_T* sprite_get_current_texture_coord(sprite_T* sprite);

void sprite_draw(sprite_T* sprite, unsigned int VBO, unsigned int EBO, unsigned int shader_program, float x, float y, float z);

void sprite_update(sprite_T* sprite);
#endif
