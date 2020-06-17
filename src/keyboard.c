#include "include/keyboard.h"
#include "include/application.h"
#include <GLFW/glfw3.h>
#include <string.h>


extern application_T* APP;
extern keyboard_T* KEYBOARD;


keyboard_T* init_keyboard()
{
    keyboard_T* keyboard = calloc(1, sizeof(struct KEYBOARD_STRUCT));

    return keyboard;
}

void keyboard_tick()
{
    if (keyboard_check_pressed_once(GLFW_KEY_F2))
        APP->debug_mode = !APP->debug_mode;

    if (keyboard_check_pressed_once(GLFW_KEY_F3))
        APP->limit_fps = !APP->limit_fps;
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
    memset(keyboard->keys, GLFW_RELEASE, sizeof(int) * KEYBOARD_NR_KEYS);
}
