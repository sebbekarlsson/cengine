#include <cengine/main.h>
#include <cengine/application.h>
#include "include/main.h"
#include "include/ikea_scene.h"

extern unsigned int TEXTURE_TILES;
extern texture_T* TEXTURE_CHARACTER_TILES;


extern application_T* APP;


/**
 * Below is just a test program to test the API.
 * TODO: remove
 */
int main(int argc, char* argv[])
{
    APP = init_application(640, 480, "App");
    //APP->debug_mode = 1;

    TEXTURE_TILES = texture_get_id("res/image/tiles.png");
    TEXTURE_CHARACTER_TILES = texture_get("res/image/oga_sheet.png");

    application_add_scene(APP, (scene_T*) init_ikea_scene());

    return cengine_main(argc, argv);
}
