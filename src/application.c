#include "include/application.h"
#include "include/shader.h"


application_T* init_application(int width, int height, const char* title)
{
    application_T* app = calloc(1, sizeof(struct APPLICATION_STRUCT));
    app->scene_index = 0;
    app->scenes = init_dynamic_list(sizeof(struct SCENE_STRUCT*));

    app->window = init_window(width, height, title);

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

    app->delta_time = 0;
    app->current_time = application_get_time();
    app->last_time = app->current_time;

    app->fps = 0;
    app->frames = 0;
    app->fps_delta_time = 0;
    app->fps_last_time = 0;

    app->limit_fps = 1;

    return app;
}

void application_free(application_T* app)
{
    printf("Trying to deallocate %ld scenes...\n", app->scenes->size);

    for (int i = 0; i < app->scenes->size; i++)
    {
        scene_T* scene = (scene_T*) app->scenes->items[i];

        if (!scene->free)
        {
            printf("WARNING: Scene `%d` is missing a free method.\n", i);
            scene_free(scene);
            continue;
        }

        scene->free(scene);
        scene_free(scene);
    }

    printf("Calling window_free...\n");
    
    window_free(app->window);
    
    printf("Deallocating shaders...\n");

    glDeleteProgram(app->shader_program_default);
    glDeleteProgram(app->shader_program_text);
    glDeleteProgram(app->shader_program_color);

    printf("Deallocating application...\n");

    free(app);
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
