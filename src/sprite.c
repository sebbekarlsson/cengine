#include "include/sprite.h"
#include "include/application.h"

extern application_T* APP;


sprite_T* init_sprite()
{
    sprite_T* sprite = calloc(1, sizeof(struct SPRITE_STRUCT));
    sprite->textures = init_dynamic_list(sizeof(struct TEXTURE_STRUCT*));
    sprite->index = 0;
    sprite->timer = application_get_time(APP);
    sprite->delay = 1;
    sprite->animated = 1;
    sprite->flip_x = 0;
    sprite->flip_y = 0;
    sprite->draw_program = init_draw_program(APP->shader_program_default);
    draw_program_genbuffers(sprite->draw_program);

    return sprite;
}

sprite_T* init_sprite_with_texture(texture_T* texture)
{
    sprite_T* sprite = init_sprite();
    sprite_add_texture(sprite, texture);

    return sprite;
}

void sprite_free(sprite_T* sprite)
{
    // TODO: free textures list.
    
    printf("Deallocating draw program within sprite...\n");
    draw_program_free(sprite->draw_program);

    free(sprite);
}

void sprite_add_texture(sprite_T* sprite, texture_T* texture)
{
    dynamic_list_append(sprite->textures, texture);
}

texture_T* sprite_get_current_texture(sprite_T* sprite)
{
    return sprite->textures->items[sprite->index];
}

void sprite_draw(sprite_T* sprite, float x, float y, float z)
{
    texture_T* texture = (texture_T*)sprite_get_current_texture(sprite);

    draw_options_T draw_options = DRAW_OPTIONS_INIT;
    draw_options.texture = texture->id;
    draw_options.x = x;
    draw_options.y = y;
    draw_options.z = z;
    draw_options.width = texture->width;
    draw_options.height = texture->height;
    draw_options.r = 255;
    draw_options.g = 255;
    draw_options.b = 255;
    draw_options.shift_x = texture->shift_x;
    draw_options.shift_y = texture->shift_y;
    draw_options.atlas_width = texture->atlas_width;
    draw_options.atlas_height = texture->atlas_height;
    draw_options.flip_x = sprite->flip_x;
    draw_options.flip_y = sprite->flip_y;

    draw_texture(
        sprite->draw_program,
        draw_options
    );
}

void sprite_tick(sprite_T* sprite)
{
    if (!sprite->animated)
        return;

    double this_time = application_get_time(APP);

    if (this_time - sprite->timer >= sprite->delay)
    {
        sprite->index = sprite->index < sprite->textures->size-1 ? sprite->index+1 : 0;
        sprite->timer = application_get_time(APP);
    }
}
