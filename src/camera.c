#include "include/camera.h"
#include "include/matrix.h"
#include "include/application.h"
#include <stdlib.h>
#include <GL/glew.h>


extern application_T* APP;


camera_T* init_camera(float x, float y, float z)
{
    camera_T* camera = calloc(1, sizeof(struct CAMERA_STRUCT));
    actor_constructor((actor_T*)camera, x, y, z);
    
    mat4 v = GLM_MAT4_IDENTITY_INIT;
    glm_mat4_copy(v, camera->view);

    camera->offset_x = 0;
    camera->offset_y = 0;
    camera->offset_z = 0;

    camera->fov = 100.0f;

    camera->reverse = 0;

    switch (APP->dimensions)
    {
        case 2: glm_ortho(0.0f, APP->width, APP->height, 0, -10.0f, 100.0f, camera->projection); break;
        case 3: glm_perspective(
                    glm_rad(camera->fov),
                    (float) APP->width / (float) APP->height,
                    0.01f, 1000.0f,
                    camera->projection
                ); break;
        default: { printf("Cannot create an application with %d dimensions.\n", APP->dimensions); exit(1); } break;
    }

    return camera;
}

/**
 * Bind camera, called when you want to render something within the scope of
 * a camera, if used; make sure to call camera_unbind when done.
 * This function modifies the translation to the camera position.
 *
 * @param camera_T* camera
 */
void camera_bind(camera_T* camera)
{
    actor_T* a = (actor_T*) camera;

    matrix_generate(
        -a->x,
        -a->y,
        -a->z,
        -a->rx,
        -a->ry,
        -a->rz,
        camera->offset_x,
        camera->offset_y,
        camera->offset_z,
        camera->reverse,
        camera->view
    );

    camera_send_view_to_shader(camera, APP->shader_program_default);
    camera_send_view_to_shader(camera, APP->shader_program_text);
    camera_send_view_to_shader(camera, APP->shader_program_color);
}

/**
 * To be called after camera_bind has been called.
 * This resets the translation.
 *
 * @param camera_T* camera
 */
void camera_unbind(camera_T* camera)
{
    actor_T* a = (actor_T*) camera;

    glm_translate(camera->view, (vec3){a->x, a->y, a->z});
    
    camera_send_view_to_shader(camera, APP->shader_program_default);
    camera_send_view_to_shader(camera, APP->shader_program_text);
    camera_send_view_to_shader(camera, APP->shader_program_color);
}

void camera_send_view_to_shader(camera_T* camera, unsigned int shader_program)
{
    glUseProgram(shader_program);

    glUniformMatrix4fv(
        glGetUniformLocation(
            shader_program,
            "view"
        ),
        1,
        GL_FALSE,
        (const GLfloat*)
        camera->view
    );
}

void camera_set_x(camera_T* camera, float x)
{
    ((actor_T*)camera)->x = x;
}

void camera_set_y(camera_T* camera, float y)
{
    ((actor_T*)camera)->y = y;
}
