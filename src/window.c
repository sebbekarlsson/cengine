#include "include/window.h"
#include "include/application.h"
#include <stdio.h>
#include <stdlib.h>


extern application_T* APP;


static void window_error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

static void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

GLFWwindow* init_window(int width, int height, const char* title)
{
    GLFWwindow* window;
 
    glfwSetErrorCallback(window_error_callback);
 
    if (!glfwInit())
        exit(EXIT_FAILURE);
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_FLOATING, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
 
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
 
    glfwSetKeyCallback(window, window_key_callback);
 
    glfwMakeContextCurrent(window);
    
    GLenum err = glewInit();

    if (GLEW_OK != err)
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    glfwSwapInterval(1);

    return window;
}

double window_mouse_get_x()
{
    double xpos, ypos;
    glfwGetCursorPos(APP->window, &xpos, &ypos);

    return xpos;
}

double window_mouse_get_y()
{
    double xpos, ypos;
    glfwGetCursorPos(APP->window, &xpos, &ypos);

    return ypos;
}
