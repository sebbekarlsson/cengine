#ifndef CENGINE_APPLICATION_H
#define CENGINE_APPLICATION_H
#include "scene.h"
#include "dynamic_list.h"
#include "window.h"


typedef struct APPLICATION_STRUCT
{
    int scene_index;
    dynamic_list_T* scenes;

    int width;
    int height;
    GLFWwindow* window;

    // shaders
    unsigned int shader_program_default;
    unsigned int shader_program_text;

    // time
    double delta_time;
    double current_time;
    double last_time; 
} application_T;

application_T* init_application(int width, int height, const char* title);

scene_T* application_add_scene(application_T* application, scene_T* scene);

scene_T* application_get_current_scene(application_T* application);

double application_get_time();
#endif
