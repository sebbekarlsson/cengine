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
    scene->actors = init_dynamic_list(sizeof(struct ACTOR_STRUCT*));

    glGenVertexArrays(1, &scene->VAO);

    scene->tick = (void*) 0;
    scene->draw = (void*) 0;

    scene->camera = init_camera(0, 0, 0);

    return scene;
}

void scene_tick(scene_T* scene)
{
    for (int i = 0; i < scene->actors->size; i++)
    {
        actor_T* actor = (actor_T*) scene->actors->items[i];

        physics_tick_actor(actor); 

        if (actor->tick)
            actor->tick(actor); 
    }

    if (scene->tick)
        scene->tick(scene);
}

void scene_draw(scene_T* scene)
{
    actor_T* actor_camera = (actor_T*) scene->camera;

    glBindVertexArray(scene->VAO);

    GLuint view_location = glGetUniformLocation(
        APP->shader_program_default,
        "view"
    );

    mat4 v = GLM_MAT4_IDENTITY_INIT;
    glm_translate(
        v,
        (vec3){ -actor_camera->x, -actor_camera->y, -actor_camera->z }
    );

    glUniformMatrix4fv(view_location, 1, GL_FALSE, (const GLfloat*) v);

    for (int i = 0; i < scene->actors->size; i++)
    {
        actor_T* actor = (actor_T*) scene->actors->items[i];

        if (actor->draw)
            actor->draw(actor);
    }

    if (scene->draw)
        scene->draw(scene);
}

void scene_add_actor(scene_T* scene, actor_T* actor)
{
    dynamic_list_append(scene->actors, actor);
}
