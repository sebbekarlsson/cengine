#include "include/sprite.h"


sprite_T* init_sprite()
{
    sprite_T* sprite = calloc(1, sizeof(struct SPRITE_STRUCT));
    sprite->textures = init_dynamic_list(sizeof(struct TEXTURE_STRUCT*));
    sprite->index = 0;

    return sprite;
}

sprite_T* init_sprite_with_texture(texture_T* texture)
{
    sprite_T* sprite = init_sprite();
    sprite_add_texture(sprite, texture);

    return sprite;
}

void sprite_add_texture(sprite_T* sprite, texture_T* texture)
{
    dynamic_list_append(sprite->textures, texture);
}

texture_T* sprite_get_current_texture(sprite_T* sprite)
{
    return sprite->textures->items[sprite->index];
}
