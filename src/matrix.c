#include "include/matrix.h"


void matrix_generate(
    float trans_x,
    float trans_y,
    float trans_z,
    float rot_x,
    float rot_y,
    float rot_z,
    float offset_x,
    float offset_y,
    float offset_z,
    unsigned int reverse,
    mat4 final
)
{
    vec4 qx, qy, qz;
    mat4 mx, my, mz;

    glm_quat(qx, glm_rad(rot_x), 1.0f, 0.0f, 0.0f);
    glm_quat(qy, glm_rad(rot_y), 0.0f, 1.0f, 0.0f);
    glm_quat(qz, glm_rad(rot_z), 0.0f, 0.0f, 1.0f);

    glm_quat_mat4(qx, mx);
    glm_quat_mat4(qy, my);
    glm_quat_mat4(qz, mz);

    mat4 trans = GLM_MAT4_IDENTITY_INIT;
    mat4 trans_two = GLM_MAT4_IDENTITY_INIT; 
    mat4 trans_pos = GLM_MAT4_IDENTITY_INIT; 
    mat4 rot = GLM_MAT4_IDENTITY_INIT; 

    glm_mat4_mulN((mat4* []){&mx, &my, &mz}, 3, rot);

    if (!reverse)
    {
        glm_translate(trans, (vec3){ trans_x+offset_x, trans_y+offset_y, trans_z+offset_z });
        glm_translate(trans_two, (vec3){ -(trans_x+offset_x), -(trans_y+offset_y), -(trans_z+offset_z) });
    }
    else
    {
        glm_translate(trans_two, (vec3){ trans_x+offset_x, trans_y+offset_y, trans_z+offset_z });
        glm_translate(trans, (vec3){ -(trans_x+offset_x), -(trans_y+offset_y), -(trans_z+offset_z) });
    }

    glm_translate(trans_pos, (vec3){ trans_x, trans_y, trans_z });

    glm_mat4_mulN((mat4* []){&trans, &rot, &trans_two, &trans_pos}, 4, final);
}
