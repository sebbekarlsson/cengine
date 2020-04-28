#include "include/application.h"
#include "include/shader.h"


application_T* init_application(int width, int height, int dimensions, const char* title)
{
    application_T* app = calloc(1, sizeof(struct APPLICATION_STRUCT));
    app->scene_index = 0;
    app->scenes = init_dynamic_list(sizeof(struct SCENE_STRUCT*));

    app->width = width;
    app->height = height;

    app->dimensions = dimensions;

    app->window = init_window(app->width, app->height, title);

    app->shader_program_default = init_shader_program_from_file(
        "/usr/local/share/cengine/res/shader/vertex.glsl",        
        "/usr/local/share/cengine/res/shader/fragment.glsl" 
    );

    app->shader_program_text = init_shader_program_from_file(
        "/usr/local/share/cengine/res/shader/vertex.glsl",        
        "/usr/local/share/cengine/res/shader/text_fragment.glsl" 
    );

    app->shader_program_color = init_shader_program_from_file(
        "/usr/local/share/cengine/res/shader/vertex.glsl",        
        "/usr/local/share/cengine/res/shader/color_fragment.glsl" 
    );

    app->debug_mode = 0;

    app->current_time = application_get_time();
    app->last_time = app->current_time; 

    return app;
}

scene_T* application_add_scene(application_T* application, scene_T* scene)
{
    dynamic_list_append(application->scenes, scene);

    return scene;
}

scene_T* application_get_current_scene(application_T* application)
{
    return (scene_T*) application->scenes->items[application->scene_index];
}

double application_get_time()
{
    return glfwGetTime();
}
