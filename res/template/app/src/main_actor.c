#include "include/main_actor.h"


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

    draw_line(
        self->draw_program,
        self->x, self->y + self->hitbox_height/2, self->z,
        self->x + self->hitbox_width, self->y + self->hitbox_height/2, self->z,
        255, 0, 0, 1.0f 
    );
    draw_line(
        self->draw_program,
        self->x + self->hitbox_width/2, self->y, self->z,
        self->x + self->hitbox_width/2, self->y + self->hitbox_height, self->z,
        255, 0, 0, 1.0f 
    );
}
