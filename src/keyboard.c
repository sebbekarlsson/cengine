#include "include/keyboard.h"
#include "include/application.h"
#include <GLFW/glfw3.h>


extern application_T* APP;


int keyboard_check_pressed(int key)
{
    return glfwGetKey(APP->window, key) == GLFW_PRESS;
}

int keyboard_check_released(int key)
{
    return glfwGetKey(APP->window, key) == GLFW_RELEASE;
}
