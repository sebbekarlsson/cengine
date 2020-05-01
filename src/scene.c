#include "include/scene.h"
#include "include/actor.h"
#include "include/physics.h"
#include "include/application.h"
#include <GL/glew.h>
#include <cglm/cglm.h>
#include <cglm/call.h>


extern application_T* APP;


scene_T* init_scene()
{
    scene_T* scene = calloc(1, sizeof(struct SCENE_STRUCT));
    return scene_constructor(scene);
}

scene_T* scene_constructor(scene_T* scene)
{
    scene->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT*));

    glGenVertexArrays(1, &scene->VAO);

    scene->tick = (void*) 0;
    scene->draw = (void*) 0;

    scene->camera = init_camera(0, 0, 0);

    scene->draw_program = init_draw_program(APP->shader_program_default);
    scene->draw_program_text = init_draw_program(APP->shader_program_text);
    scene->draw_program_color = init_draw_program(APP->shader_program_color);

    return scene;
}

void scene_tick(scene_T* scene)
{
    for (int i = 0; i < scene->actors->size; i++)
    {
        actor_T* actor = (actor_T*) scene->actors->items[i];

        if (actor->tick)
            actor->tick(actor);

        if (actor->sprite)
            sprite_tick(actor->sprite);
    }

    if (scene->tick)
        scene->tick(scene);
}

void scene_draw(scene_T* scene)
{
    camera_T* camera = scene->camera;

    glBindVertexArray(scene->VAO);

    camera_bind(camera); 

    for (int i = 0; i < scene->actors->size; i++)
    {
        glBindVertexArray(scene->VAO);

        actor_T* actor = (actor_T*) scene->actors->items[i];

        actor_draw_default(actor);

        if (actor->draw)
            actor->draw(actor);
    }

    camera_unbind(camera);
    
    glBindVertexArray(scene->VAO);

    if (scene->draw)
        scene->draw(scene);
}

actor_T* scene_add_actor(scene_T* scene, actor_T* actor)
{
    dynamic_list_append(scene->actors, actor);

    return actor;
}
