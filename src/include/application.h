#ifndef CENGINE_APPLICATION_H
#define CENGINE_APPLICATION_H
#include "scene.h"
#include "dynamic_list.h"
#include "window.h"


typedef struct APPLICATION_STRUCT
{
    int scene_index;
    dynamic_list_T* scenes;

    window_T* window;

    // shaders
    unsigned int shader_program_default;
    unsigned int shader_program_text;
    unsigned int shader_program_color;

    // booleans
    unsigned int debug_mode;

    // time
    double delta_time;
    double current_time;
    double last_time;

    // fps calculations
    double fps;
    unsigned int frames;
    double fps_delta_time;
    double fps_last_time;

    unsigned int limit_fps;
} application_T;

application_T* init_application(int width, int height, const char* title);

void application_free(application_T* app);

scene_T* application_add_scene(application_T* application, scene_T* scene);

scene_T* application_get_current_scene(application_T* application);

double application_get_time();
#endif
