#include "include/draw.h"


void draw_texture(
    unsigned int VBO,
    unsigned int EBO,
    unsigned int shader_program,
    unsigned int texture,
    float x, float y, float z,
    int width,
    int height,
    float r,
    float g,
    float b,
    float a,
    int shift_x,
    int shift_y,
    int atlas_width,
    int atlas_height,
    unsigned int flip_x,
    unsigned int flip_y
)
{
    float vertices[] =
    {
        // positions            // colors                                // texture coords
        0.0f,   0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   0.0f, 0.0f,    shift_x, shift_y,   // top right
        width,   0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   1.0f, 0.0f,   shift_x, shift_y,  // bottom right
        width,   height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   1.0f, 1.0f,   shift_x, shift_y,  // bottom left
        0.0f,   height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   0.0f, 1.0f,    shift_x, shift_y   // top left
    };

    unsigned int indices [] =
    {
        0, 1, 3,   // first triangle
        1, 2, 3    // second triangle
    };

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glUniform1i(glGetUniformLocation(shader_program, "u_texture"), 0); 

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // translate
    mat4 m = GLM_MAT4_IDENTITY_INIT;
    glm_translate(m, (vec3){x, y, z});
    
    GLuint model_location = glGetUniformLocation(shader_program, "model");
    glUniformMatrix4fv(model_location, 1, GL_FALSE, (const GLfloat*) m);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    // texcoords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // shiftX
    glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(9 * sizeof(float)));
    glEnableVertexAttribArray(3);

    // shiftY
    glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, 11 * sizeof(float), (void*)(10 * sizeof(float)));
    glEnableVertexAttribArray(4);

    glUniform1i(glGetUniformLocation(shader_program, "atlas_width"), atlas_width);
    glUniform1i(glGetUniformLocation(shader_program, "atlas_height"), atlas_height);
    
    glUniform1i(glGetUniformLocation(shader_program, "flip_x"), flip_x);
    glUniform1i(glGetUniformLocation(shader_program, "flip_y"), flip_y);

    glUniform3fv(glGetUniformLocation(shader_program, "world_pos"), 1, (float[]){ x, y, z });

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}
