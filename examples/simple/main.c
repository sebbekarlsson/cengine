#include <cengine/main.h>
#include <cengine/application.h>


extern application_T* APP;


scene_T* init_main_scene()
{
    scene_T* scene = init_scene();

    texture_T* texture = texture_get("res/banana.png");

    actor_T* actor = init_actor(
        (APP->width / 2) - texture->width / 2,
        (APP->height / 2) - texture->height / 2,
        0
    );

    actor->sprite = init_sprite_with_texture(texture);

    scene_add_actor(scene, actor);

    return scene;
}


int main(int argc, char* argv[])
{
    APP = init_application(640, 480, 3, "App"); 

    application_add_scene(APP, init_main_scene());

    return cengine_main(argc, argv);
}
