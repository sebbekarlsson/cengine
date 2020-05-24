#include "include/main_actor.h"
#include <cengine/draw_options.h>


main_actor_T* init_main_actor(float x, float y, float z)
{
    main_actor_T* main_actor = calloc(1, sizeof(struct MAIN_ACTOR_STRUCT));
    actor_T* actor = actor_constructor((actor_T*) main_actor, x, y, z);

    actor->tick = main_actor_tick;
    actor->draw = main_actor_draw;

    return main_actor;
}

void main_actor_tick(actor_T* self)
{
    // move the actor for demonstrational purposes
    
    self->x += 0.5f;
    self->y += 0.5f;
}

void main_actor_draw(actor_T* self)
{

    // Just drawing a cross for demonstrational purposes
    
    draw_options_T horizontal = DRAW_OPTIONS_INIT;
    horizontal.x = self->x;
    horizontal.y = self->y + self->hitbox_height / 2;
    horizontal.z = self->z;
    horizontal.endx = self->x + self->hitbox_width;
    horizontal.endy = self->y + self->hitbox_height / 2;
    horizontal.endz = self->z;
    horizontal.r = 255;
    horizontal.g = 0;
    horizontal.b = 0;

    draw_line(
        self->draw_program,
        horizontal
    );

    draw_options_T vertical = DRAW_OPTIONS_INIT;
    vertical.x = self->x + self->hitbox_width / 2;
    vertical.y = self->y;
    vertical.z = self->z;
    vertical.endx = self->x + self->hitbox_width/2;
    vertical.endy = self->y + self->hitbox_height;
    vertical.endz = self->z;
    vertical.r = 255;
    vertical.g = 0;
    vertical.b = 0;

    draw_line(
        self->draw_program,
        vertical
    );
}
