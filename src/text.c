#include "include/text.h"
#include <GL/glew.h>
#include <stdio.h>
#include <string.h>
#include <ft2build.h>
#include FT_FREETYPE_H


text_character_T* init_text_character()
{
    text_character_T* character = calloc(1, sizeof(struct TEXT_CHARACTER_STRUCT));
    character->id = 0;
    character->width = 0;
    character->height = 0;
    character->bearing_left = 0;
    character->bearing_top = 0;
    character->advance = 0;

    return character;
}

dynamic_list_T* get_text_characters_from_text(const char* text, const char* fontpath, int size)
{
    dynamic_list_T* list = init_dynamic_list(sizeof(struct TEXT_CHARACTER_STRUCT));
    unsigned int text_length = strlen(text);


    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        printf("ERROR::FREETYPE: Could not init FreeType Library\n");
        exit(1);
    }

    FT_Face face;
    if (FT_New_Face(ft, fontpath, 0, &face))
    {
        printf("ERROR::FREETYPE: Failed to load font\n");
        exit(1);
    }

    FT_Set_Pixel_Sizes(face, 0, size);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (int i = 0; i < text_length; i++)
    {
        char c = text[i];

        // Load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            printf("ERROR::FREETYTPE: Failed to load Glyph (%c)\n", c);
            continue;
        }

        // Generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // Set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        text_character_T* character = init_text_character();
        character->width = face->glyph->bitmap.width;
        character->height = face->glyph->bitmap.rows;
        character->bearing_left = face->glyph->bitmap_left;
        character->bearing_top = face->glyph->bitmap_top;
        character->advance = face->glyph->advance.x;
        character->id = texture;

        // Now store character for later use
        dynamic_list_append(list, character);
    }

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return list;
}

void text_character_free(text_character_T* character)
{
    glDeleteTextures(1, &character->id);
    free(character);
}

static void _text_character_free(void* item)
{
    text_character_free((text_character_T*) item);
}

void text_character_list_free(dynamic_list_T* list)
{
    dynamic_list_free(list, _text_character_free);
}
