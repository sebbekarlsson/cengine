#ifndef CENGINE_KEYBOARD_H
#define CENGINE_KEYBOARD_H

#define KEYBOARD_NR_KEYS 300

typedef struct KEYBOARD_STRUCT {
    int keys[KEYBOARD_NR_KEYS];
} keyboard_T;

keyboard_T* init_keyboard();

int keyboard_check_pressed(int key);

int keyboard_check_pressed_once(int key);

int keyboard_check_released(int key);

void keyboard_reset_keys(keyboard_T* keyboard);
#endif
