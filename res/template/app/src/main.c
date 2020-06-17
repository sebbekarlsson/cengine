#include <cengine/main.h>
#include <cengine/application.h>
#include "include/main_scene.h"


extern application_T* APP;


int main(int argc, char* argv[])
{
    APP = init_application(640, 480, "App");

    application_add_scene(APP, (scene_T*) init_main_scene());

    return cengine_main(argc, argv);
}
