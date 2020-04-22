#include "include/draw.h"
#include "include/text.h"
#include "include/application.h"


extern application_T* APP;


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
    glUseProgram(shader_program);

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

static void draw_character(
    unsigned int VBO,
    unsigned int EBO,
    unsigned int shader_program,
    text_character_T* character,
    float x, float y, float z,
    float r, float g, float b, float a,
    int width, int height
)
{
    glUseProgram(shader_program);

    int shift_x = 0;
    int shift_y = 0;

    float vertices[] =
    {
        // positions            // colors                                // texture coords
        0.0f,   0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   0.0f, 1.0f,    shift_x, shift_y,   // top right
        width,   0.0f,    0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   1.0f, 1.0f,   shift_x, shift_y,  // bottom right
        width,   -height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   1.0f, 0.0f,   shift_x, shift_y,  // bottom left
        0.0f,   -height,  0.0f,  r / 255.0f, g / 255.0f, b / 255.0f, a,   0.0f, 0.0f,    shift_x, shift_y   // top left
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
    glBindTexture(GL_TEXTURE_2D, character->id);

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

    glUniform1i(glGetUniformLocation(shader_program, "atlas_width"), 0);
    glUniform1i(glGetUniformLocation(shader_program, "atlas_height"), 0);
    
    glUniform1i(glGetUniformLocation(shader_program, "flip_x"), 0);
    glUniform1i(glGetUniformLocation(shader_program, "flip_y"), 0);

    glUniform3fv(glGetUniformLocation(shader_program, "world_pos"), 1, (float[]){ x, y, z });

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void draw_text(
    unsigned int VAO,
    unsigned int VBO,
    unsigned int EBO,
    const char* text,
    const char* fontpath,
    float x, float y, float z,
    int size,
    float r, float g, float b
)
{
    dynamic_list_T* characters = get_text_characters_from_text(text, fontpath, size);

    float scale = 3.0f;

    for (int i = 0; i < characters->size; i++)
    {
        text_character_T* character = characters->items[i];

        float xpos = x + character->bearing_left * scale;
        float ypos = y - (character->height - character->bearing_top) * scale;

        float w = character->width * scale;
        float h = character->height * scale;
        
        glBindVertexArray(VAO);
        draw_character(
            VBO,
            EBO,
            APP->shader_program_text,
            character,
            xpos, ypos, z,
            255, 255, 255, 1.0f,
            w, h
        );

        x += (character->advance >> 6) * scale;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);

    text_character_list_free(characters);
}
