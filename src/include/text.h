#ifndef CENGINE_TEXT_H
#define CENGINE_TEXT_H
#include "dynamic_list.h"


typedef struct TEXT_CHARACTER_STRUCT
{
    unsigned int id;
    int width;
    int height;
    int bearing_left;
    int bearing_top;
    unsigned int advance;
} text_character_T;

text_character_T* init_text_character();

void text_character_free(text_character_T* character);

void text_character_list_free(dynamic_list_T* list);

dynamic_list_T* get_text_characters_from_text(const char* text, const char* fontpath, int size);
#endif
