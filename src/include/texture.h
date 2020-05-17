#ifndef CENGINE_TEXTURE_H
#define CENGINE_TEXTURE_H
#include <stdint.h>

typedef struct TEXTURE_STRUCT
{
    unsigned int id;
    uint32_t* data;
    int width;
    int height;
    int shift_x;
    int shift_y;
    int atlas_width;
    int atlas_height;
} texture_T;

texture_T* init_texture(unsigned int id, uint32_t* data, int width, int height);

unsigned int texture_get_id(const char* pathname);

unsigned int texture_get_cut_id(texture_T* texture, int x, int y, int w, int h);

texture_T* texture_get(const char* pathname);

void texture_free(texture_T* texture);
#endif
