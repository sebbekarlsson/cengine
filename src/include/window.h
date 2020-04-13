#ifndef CENGINE_WINDOW_H
#define CENGINE_WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* init_window(int width, int height, const char* title);

double window_mouse_get_x();

double window_mouse_get_y();
#endif
