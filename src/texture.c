#include "include/texture.h"
#include <GL/glew.h>
#include <stdlib.h>
#include <png.h>


texture_T* init_texture(unsigned int id, int width, int height)
{
    texture_T* texture = calloc(1, sizeof(struct TEXTURE_STRUCT));
    texture->id = id;
    texture->width = width;
    texture->height = height;
    texture->shift_x = 0;
    texture->shift_y = 0;
    texture->atlas_width = 1;
    texture->atlas_height = 1;

    return texture;
}

unsigned int texture_get_id(const char* pathname)
{
    texture_T* texture = texture_get(pathname);
    unsigned int id =texture->id;
    
    free(texture);

    return id;
}

texture_T* texture_get(const char* pathname)
{
    /**
     * Texture will be stored in this unsigned integer.
     */
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    /**
     * This is texture parameters,
     * you can see them as "effects" that are applied to the
     * loaded texture.
     */
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    /**
     * Using libpng to read & load a .png file
     */
    png_image image = {};
    image.version = PNG_IMAGE_VERSION;

    if (!png_image_begin_read_from_file(&image, pathname))
        fprintf(stderr, "Could not read file `%s`: %s\n", pathname, image.message);

    image.format = PNG_FORMAT_RGBA;

    /**
     * image_pixels in this case is the data we are interested in and which
     * is used for drawing later.
     */
    uint32_t *image_pixels = malloc(sizeof(uint32_t) * image.width * image.height);
    if (image_pixels == NULL)
        fprintf(stderr, "Could not allocate memory for an image\n");

    /**
     * Check for errors
     */
    if (!png_image_finish_read(&image, NULL, image_pixels, 0, NULL))
        fprintf(stderr, "libpng error: %s\n", image.message);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGBA,
                 image.width,
                 image.height,
                 0,
                 GL_RGBA,
                 GL_UNSIGNED_BYTE,
                 image_pixels);

    glGenerateMipmap(GL_TEXTURE_2D);

    return init_texture(texture, image.width, image.height);
}

void texture_free(texture_T* texture)
{
    glDeleteTextures(1, &(texture->id));
    free(texture);
}

texture_coords_T* init_texture_coords(int x, int y)
{
    texture_coords_T* texture_coords = calloc(1, sizeof(struct TEXTURE_COORDS_STRUCT));
    texture_coords->x = x;
    texture_coords->y = y;

    return texture_coords;
}
