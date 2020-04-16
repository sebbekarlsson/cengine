#include "include/sprite.h"
#include "include/draw.h"


sprite_T* init_sprite()
{
    sprite_T* sprite = calloc(1, sizeof(struct SPRITE_STRUCT));
    sprite->textures = init_dynamic_list(sizeof(struct TEXTURE_STRUCT*));
    sprite->texture_coords = init_dynamic_list(sizeof(struct TEXTURE_COORDS_STRUCT*));
    sprite->index = 0;
    sprite->coord_index = 0;

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

texture_coords_T* sprite_add_texture_coords(sprite_T* sprite, int x, int y)
{
    texture_coords_T* coords = init_texture_coords(x, y);
    dynamic_list_append(sprite->texture_coords, coords);

    return coords;
}

texture_T* sprite_get_current_texture(sprite_T* sprite)
{
    return sprite->textures->items[sprite->index];
}

texture_coords_T* sprite_get_current_texture_coord(sprite_T* sprite)
{
    return sprite->textures->items[sprite->coord_index];
}

void sprite_draw(sprite_T* sprite, unsigned int VBO, unsigned int EBO, unsigned int shader_program, float x, float y, float z)
{
    texture_T* texture = sprite_get_current_texture(sprite);
    texture_coords_T* coords = sprite_get_current_texture_coord(sprite);

    int shift_x = coords->x;
    int shift_y = coords->y;
    int atlas_width = 1;
    int atlas_height = 1;

    draw_texture(
        EBO,
        EBO,
        shader_program,
        texture->id,
        x, y, z,
        texture->width,
        texture->height,
        255,
        255,
        255,
        1.0f,
        shift_x,
        shift_y,
        atlas_width,
        atlas_height
    );
}

void sprite_update(sprite_T* sprite)
{
    sprite->index = sprite->index < sprite->textures->size-1 ? sprite->index+1 : 0;
    sprite->coord_index = sprite->coord_index < sprite->texture_coords->size-1 ? sprite->coord_index+1 : 0;
}
