#ifndef CENGINE_WINDOW_H
#define CENGINE_WINDOW_H

#define RES_WIDTH 640
#define RES_HEIGHT 480

#include <GL/glew.h>
#include <GLFW/glfw3.h>

typedef struct WINDOW_STRUCT
{
    GLFWwindow* window;
    int width;
    int height;
    int blit_start_x;
    int blit_start_y;
    int blit_w;
    int blit_h;
} window_T;

window_T* init_window(int width, int height, const char* title);

void window_free(window_T* window);

void window_recalc(window_T* window, int width, int height);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

unsigned int window_generate_framebuffer();

double window_mouse_get_x();

double window_mouse_get_y();
#endif
