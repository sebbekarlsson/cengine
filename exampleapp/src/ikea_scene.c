#include "include/ikea_scene.h"
#include "include/ikea_actor.h"
#include "include/ground_actor.h"
#include <cengine/texture.h>
#include <cengine/window.h>
#include <cengine/draw.h>
#include <cengine/application.h>


extern application_T* APP;


void ikea_scene_draw(scene_T* scene)
{
    unsigned int VBO;
    unsigned int EBO;

    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    double mx = window_mouse_get_x();
    double my = window_mouse_get_y();

    unsigned int texture = texture_get("res/image/potato.png");

    draw_texture(
        VBO,
        EBO,
        APP->shader_program_default,
        texture,
        mx, my, 0,
        32,
        32,
        255,
        255,
        255,
        1.0f
    );

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    texture_free(texture);
}

scene_T* init_ikea_scene()
{
    scene_T* scene = init_scene();
    scene->draw = ikea_scene_draw;

    scene_add_actor(scene, init_ikea_actor(0, 0, 0));

    float y = 32 * 8;
    for (int i = 0; i < 16; i++)
        scene_add_actor(scene, init_ground_actor(i * 32, y + (i*32), 0));

    return scene;
}
