#include "include/application.h"
#include "include/main.h"
#include "include/window.h"
#include "include/shader.h"
#include "include/actor.h"
#include "include/draw.h"
#include "include/texture.h"
#include "include/scene.h"


extern application_T* APP;
extern keyboard_T* KEYBOARD;


int cengine_main(int argc, char* argv[])
{
    printf("cengine is starting...\n");

    KEYBOARD = init_keyboard();

    glUseProgram(APP->shader_program_default);
    GLuint projection_location = glGetUniformLocation(APP->shader_program_default, "projection");

    glUseProgram(APP->shader_program_text);
    GLuint projection_location_text = glGetUniformLocation(APP->shader_program_text, "projection");

    glUseProgram(APP->shader_program_color);
    GLuint projection_location_color = glGetUniformLocation(APP->shader_program_color, "projection"); 
    
    printf("Calculating framebuffer...\n");
    unsigned int framebuffer = window_generate_framebuffer(APP->window); 
    
    printf("Entering main loop.\n");
    while (!glfwWindowShouldClose(APP->window->window))
    {
        scene_T* scene = application_get_current_scene(APP);

        glUseProgram(APP->shader_program_default);
        glUniformMatrix4fv(projection_location, 1, GL_FALSE, (const GLfloat*) scene->camera->projection);

        glUseProgram(APP->shader_program_text);
        glUniformMatrix4fv(projection_location_text, 1, GL_FALSE, (const GLfloat*) scene->camera->projection);

        glUseProgram(APP->shader_program_color);
        glUniformMatrix4fv(projection_location_color, 1, GL_FALSE, (const GLfloat*) scene->camera->projection);
        
        // Render to our framebuffer
        glUseProgram(APP->shader_program_default);
        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 

        glViewport(0, 0, RES_WIDTH, RES_HEIGHT);

        glClearColor(0, 0, 0, 1);
        glEnable(GL_DEPTH_TEST);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 

        scene_tick(scene);
        scene_draw(scene);

        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
        glBlitFramebuffer(
            0,
            0,
            RES_WIDTH,
            RES_HEIGHT,
            APP->window->blit_start_x,
            APP->window->blit_start_y,
            APP->window->blit_start_x + APP->window->blit_w,
            APP->window->blit_start_y + APP->window->blit_h, GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT, GL_NEAREST
        );
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glfwSwapBuffers(APP->window->window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        keyboard_reset_keys(KEYBOARD); 

        glfwPollEvents();

        APP->current_time = application_get_time();
        APP->delta_time = APP->current_time - APP->last_time;
        APP->last_time = APP->current_time;
    }

    printf("Exit main loop.\n");
    
    application_free(APP);
    
    printf("Terminating glfw..\n");
    glfwTerminate();

    printf("Done.\n");

    return 0;
}
