#include "include/application.h"
#include "include/main.h"
#include "include/window.h"
#include "include/shader.h"
#include "include/actor.h"
#include "include/draw.h"
#include "include/texture.h"
#include "include/scene.h"


extern application_T* APP;


int cengine_main(int argc, char* argv[])
{
    glUseProgram(APP->shader_program_default);
    GLuint projection_location = glGetUniformLocation(APP->shader_program_default, "projection");

    glUseProgram(APP->shader_program_text);
    GLuint projection_location_text = glGetUniformLocation(APP->shader_program_text, "projection");

    glUseProgram(APP->shader_program_color);
    GLuint projection_location_color = glGetUniformLocation(APP->shader_program_color, "projection");
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    while (!glfwWindowShouldClose(APP->window))
    {
        scene_T* scene = application_get_current_scene(APP);

        glfwGetFramebufferSize(APP->window, &APP->width, &APP->height);

        glViewport(0, 0, APP->width, APP->height);
        glClearColor(0, 0, 0, 1);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        glUseProgram(APP->shader_program_default);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*) scene->camera->projection);

        glUseProgram(APP->shader_program_text);
        glUniformMatrix4fv(projection_location_text, 1, GL_FALSE, (const GLfloat*) scene->camera->projection);

        glUseProgram(APP->shader_program_color);
        glUniformMatrix4fv(projection_location_color, 1, GL_FALSE, (const GLfloat*) scene->camera->projection);

        scene_tick(scene);
        scene_draw(scene);

        glfwSwapBuffers(APP->window);
        glfwPollEvents();

        APP->current_time = application_get_time();
        APP->delta_time = APP->current_time - APP->last_time;
        APP->last_time = APP->current_time;
    }

    glfwDestroyWindow(APP->window);
    glfwTerminate();

    return 0;
}
