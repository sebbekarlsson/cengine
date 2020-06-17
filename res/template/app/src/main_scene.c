#include "include/main_scene.h"
#include "include/main_actor.h"
#include <cengine/window.h>


main_scene_T* init_main_scene()
{
    main_scene_T* main_scene = calloc(1, sizeof(struct MAIN_SCENE_STRUCT));
    scene_T* scene = scene_constructor((scene_T*) main_scene, 2);

    scene_add_actor(
        scene,
        (actor_T*)
        init_main_actor(RES_WIDTH / 2, RES_HEIGHT / 2, 0.0f) 
    );

    return main_scene;
}
