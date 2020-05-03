#include "include/keyboard.h"
#include "include/application.h"
#include <GLFW/glfw3.h>


extern application_T* APP;
extern keyboard_T* KEYBOARD;


keyboard_T* init_keyboard()
{
    keyboard_T* keyboard = calloc(1, sizeof(struct KEYBOARD_STRUCT));

    return keyboard;
}

int keyboard_check_pressed(int key)
{
    return glfwGetKey(APP->window->window, key) == GLFW_PRESS;
}

int keyboard_check_pressed_once(int key)
{
    return KEYBOARD->keys[key] == GLFW_PRESS;
}

int keyboard_check_released(int key)
{
    return glfwGetKey(APP->window->window, key) == GLFW_RELEASE;
}

void keyboard_reset_keys(keyboard_T* keyboard)
{
    for (int i = 0; i < KEYBOARD_NR_KEYS; i++)
        keyboard->keys[i] = GLFW_RELEASE;
}
