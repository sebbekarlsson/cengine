#ifndef CENGINE_SPRITE_H
#define CENGINE_SPRITE_H
#include "dynamic_list.h"
#include "texture.h"

typedef struct SPRITE_STRUCT
{
    dynamic_list_T* textures;
    unsigned int index;
    double timer;
    float delay;
    unsigned int animated;
    unsigned int flip_x;
    unsigned int flip_y;
} sprite_T;

sprite_T* init_sprite();

sprite_T* init_sprite_with_texture(texture_T* texture);

void sprite_add_texture(sprite_T* sprite, texture_T* texture);

texture_T* sprite_get_current_texture(sprite_T* sprite);

void sprite_draw(sprite_T* sprite, unsigned int VBO, unsigned int EBO, unsigned int shader_program, float x, float y, float z);

void sprite_tick(sprite_T* sprite);
#endif
