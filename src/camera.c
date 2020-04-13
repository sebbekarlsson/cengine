#include "include/camera.h"
#include <stdlib.h>


camera_T* init_camera(float x, float y, float z)
{
    camera_T* camera = calloc(1, sizeof(struct CAMERA_STRUCT));
    actor_constructor((actor_T*)camera, x, y, z);

    return camera;
}
