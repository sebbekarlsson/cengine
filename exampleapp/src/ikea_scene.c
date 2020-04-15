#include "include/ikea_scene.h"
#include "include/ikea_actor.h"
#include "include/ground_actor.h"
#include "include/perlin.h"
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

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 0);

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
        1.0f,
        0,
        0,
        0,
        0
    );

    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    texture_free(texture);

    glUseProgram(APP->shader_program_default);
    glUniform1i(glGetUniformLocation(APP->shader_program_default, "lighting_enabled"), 1);
}

static int _round(float num)
{
    return (int)(num < 0 ? (num - 0.5) : (num + 0.5));
}

scene_T* init_ikea_scene()
{
    scene_T* scene = init_scene();
    scene->draw = ikea_scene_draw;

    scene_add_actor(scene, (actor_T*)init_ikea_actor(0, -300, 0));

    for (int i = 0; i < 128; i++)
    {
        float h = _round(perlin_get2d(i, 0, 0.1f, 20.0f) * 12);

        for (int y = 0; y < h; y++)
            scene_add_actor(scene, init_ground_actor(i * 32, -(y*32), 0));
    }

    return scene;
}
