#ifndef CENGINE_TEXTURE_H
#define CENGINE_TEXTURE_H

typedef struct TEXTURE_STRUCT
{
    unsigned int id;
    int width;
    int height;
    int shift_x;
    int shift_y;
    int atlas_width;
    int atlas_height;
} texture_T;

texture_T* init_texture(unsigned int id, int width, int height);

unsigned int texture_get_id(const char* pathname);

texture_T* texture_get(const char* pathname);

void texture_free(texture_T* texture);

typedef struct TEXTURE_COORDS_STRUCT
{
    int x;
    int y;
} texture_coords_T;

texture_coords_T* init_texture_coords(int x, int y);
#endif
