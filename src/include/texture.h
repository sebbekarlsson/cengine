#ifndef CENGINE_TEXTURE_H
#define CENGINE_TEXTURE_H

typedef struct TEXTURE_STRUCT
{
    unsigned int id;
    int width;
    int height;
} texture_T;

texture_T* init_texture(unsigned int id, int width, int height);

unsigned int texture_get_id(const char* pathname);

texture_T* texture_get(const char* pathname);

void texture_free(texture_T* texture);
#endif
