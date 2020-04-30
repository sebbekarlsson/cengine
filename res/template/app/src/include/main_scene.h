#ifndef APP_MAIN_SCENE_H
#define APP_MAIN_SCENE_H
#include <cengine/scene.h>


typedef struct MAIN_SCENE_STRUCT
{
    scene_T base;
} main_scene_T;

main_scene_T* init_main_scene();
#endif
