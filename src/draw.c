#include "include/draw.h"
#include "include/text.h"
#include "include/application.h"
#include "include/matrix.h"


extern application_T* APP;

void draw_quad(
    draw_program_T* draw_program,
    draw_options_T draw_options
)
{
    unsigned int should_delete;

    if (!draw_program->generated)
    {
        should_delete = 1;
        draw_program_genbuffers(draw_program);
    }

    glUseProgram(draw_program->shader_program);

    int shift_x = draw_options.shift_x;
    int shift_y = draw_options.shift_y;
    int width = draw_options.width;
    int height = draw_options.height;
    float r = draw_options.r;
    float g = draw_options.g;
    float b = draw_options.b;
    float a = draw_options.a;

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

    glBindBuffer(GL_ARRAY_BUFFER, draw_program->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, draw_program->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glUniform1i(glGetUniformLocation(draw_program->shader_program, "u_texture"), 0); 

    // translate
    mat4 m = GLM_MAT4_IDENTITY_INIT;
    draw_options_get_matrix(draw_options, m);
    
    GLuint model_location = glGetUniformLocation(draw_program->shader_program, "model");
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

    glUniform1i(glGetUniformLocation(draw_program->shader_program, "atlas_width"), draw_options.atlas_width);
    glUniform1i(glGetUniformLocation(draw_program->shader_program, "atlas_height"), draw_options.atlas_height); 

    glUniform1i(glGetUniformLocation(draw_program->shader_program, "flip_x"), draw_options.flip_x);
    glUniform1i(glGetUniformLocation(draw_program->shader_program, "flip_y"), draw_options.flip_y); 

    glUniform3fv(glGetUniformLocation(draw_program->shader_program, "world_pos"), 1, (float[]){ draw_options.x, draw_options.y, draw_options.z });
    
    glUniform1f(glGetUniformLocation(draw_program->shader_program, "time"), (float) application_get_time());

    glUniform1f(glGetUniformLocation(draw_program->shader_program, "pan_x"), draw_options.pan_x);
    glUniform1f(glGetUniformLocation(draw_program->shader_program, "pan_y"), draw_options.pan_y);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    if (should_delete)
        draw_program_deletebuffers(draw_program);
}

void draw_texture(
    draw_program_T* draw_program,
    draw_options_T draw_options
)
{
    unsigned int should_delete;

    if (!draw_program->generated)
    {
        should_delete = 1;
        draw_program_genbuffers(draw_program);
    }

    glUseProgram(draw_program->shader_program);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, draw_options.texture);

    draw_quad(draw_program, draw_options);
    
    if (should_delete)
        draw_program_deletebuffers(draw_program);
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

    glBindTexture(GL_TEXTURE_2D, 0);
}

void draw_text(
    draw_program_T* draw_program,
    draw_options_T draw_options
)
{
    unsigned int should_delete;

    if (!draw_program->generated)
    {
        should_delete = 1;
        draw_program_genbuffers(draw_program);
    }

    dynamic_list_T* characters = get_text_characters_from_text(draw_options.text, draw_options.fontpath, draw_options.font_size);

    float scale = 1.0f;

    float x = draw_options.x;
    float y = draw_options.y;

    for (int i = 0; i < characters->size; i++)
    {
        text_character_T* character = characters->items[i];

        float xpos = x + character->bearing_left * scale;
        float ypos = y - (character->height - character->bearing_top) * scale;

        float w = character->width * scale;
        float h = character->height * scale;
        
        draw_character(
            draw_program->VBO,
            draw_program->EBO,
            draw_program->shader_program,
            character,
            xpos, ypos, draw_options.z,
            draw_options.r, draw_options.g, draw_options.b, draw_options.a,
            w, h
        );

        x += (character->advance >> 6) * scale;
    } 

    text_character_list_free(characters);

    if (should_delete)
        draw_program_deletebuffers(draw_program);
}

void draw_line(
    draw_program_T* draw_program,
    draw_options_T draw_options
)
{
    glUseProgram(draw_program->shader_program);

    unsigned int should_delete = 0;

    if (!draw_program->generated)
    {
        should_delete = 1;
        draw_program_genbuffers(draw_program);
    }

    // translate
    mat4 m = GLM_MAT4_IDENTITY_INIT;
    glm_translate(m, (vec3){0, 0, 0});
    
    glUniformMatrix4fv(
        glGetUniformLocation(
            draw_program->shader_program, "model"
        ), 1, GL_FALSE, (const GLfloat*) m
    );
    
    float x = draw_options.x;
    float y = draw_options.y;
    float z = draw_options.z;
    float endx = draw_options.endx;
    float endy = draw_options.endy;
    float endz = draw_options.endz;
    float r = draw_options.r;
    float g = draw_options.g;
    float b = draw_options.b;
    float a = draw_options.a;

    float VERTICES[] =
    {
        // positions               // colors                             
        x,       y,       z,       r / 255.0f, g / 255.0f, b / 255.0f, a,
        endx,    endy,    endz,    r / 255.0f, g / 255.0f, b / 255.0f, a
    };

    glBindBuffer(GL_ARRAY_BUFFER, draw_program->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3* sizeof(float)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_LINES, 0, 3);
    
    //glBindVertexArray(0);

    if (should_delete)
        draw_program_deletebuffers(draw_program);
}
