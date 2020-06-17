#include "include/debug.h"
#include "include/draw.h"
#include "include/application.h"
#include <string.h>

extern application_T* APP;

void debug_tick()
{
}

static void draw_debug_bg(float x, float y, float z, float width, float height)
{
    scene_T* scene = application_get_current_scene(APP);

    draw_options_T options = DRAW_OPTIONS_INIT;
    options.x = x;
    options.y = y;
    options.z = z;
    options.width = width;
    options.height = height;
    options.r = 48;
    options.g = 48;
    options.b = 48;
    options.a = DEBUG_BG_ALPHA;

    draw_quad(
        scene->draw_program_color,
        options
    );
}

static size_t draw_debug_delta_time(float x, float y, float z, int fontsize)
{
    char* str = calloc(225, sizeof(char));
    sprintf(str, "delta: %1.6f", APP->delta_time);
    size_t size = strlen(str);

    scene_T* scene = application_get_current_scene(APP);

    draw_options_T options = DRAW_OPTIONS_INIT;
    options.x = x;
    options.y = y + DEBUG_FONT_SIZE;
    options.z = z;
    options.r = 255;
    options.g = 255;
    options.b = 255;
    options.fontpath = DEBUG_FONT;
    options.font_size = fontsize;
    options.text = str;

    draw_text(
        scene->draw_program_text,
        options        
    );

    free(str);

    return size;
}

static size_t draw_debug_nr_actors(float x, float y, float z, int fontsize)
{
    scene_T* scene = application_get_current_scene(APP);

    char* str = calloc(225, sizeof(char));
    sprintf(str, "actors: %d", (int) scene->actors->size);
    size_t size = strlen(str);

    draw_options_T options = DRAW_OPTIONS_INIT;
    options.x = x;
    options.y = y + DEBUG_FONT_SIZE;
    options.z = z;
    options.r = 255;
    options.g = 255;
    options.b = 255;
    options.fontpath = DEBUG_FONT;
    options.font_size = fontsize;
    options.text = str;

    draw_text(
        scene->draw_program_text,
        options        
    );

    free(str);

    return size;
}

static size_t draw_debug_scene_index(float x, float y, float z, int fontsize)
{
    scene_T* scene = application_get_current_scene(APP);

    char* str = calloc(128, sizeof(char));
    sprintf(str, "scene: %d", (int) APP->scene_index);
    size_t size = strlen(str);

    draw_options_T options = DRAW_OPTIONS_INIT;
    options.x = x;
    options.y = y + DEBUG_FONT_SIZE;
    options.z = z;
    options.r = 255;
    options.g = 255;
    options.b = 255;
    options.fontpath = DEBUG_FONT;
    options.font_size = fontsize;
    options.text = str;

    draw_text(
        scene->draw_program_text,
        options        
    );

    free(str);

    return size;
}

static size_t draw_debug_dimensions(float x, float y, float z, int fontsize)
{
    scene_T* scene = application_get_current_scene(APP);

    char* str = calloc(128, sizeof(char));
    sprintf(str, "(%dD)", (int) scene->camera->dimensions);
    size_t size = strlen(str);

    draw_options_T options = DRAW_OPTIONS_INIT;
    options.x = x;
    options.y = y + DEBUG_FONT_SIZE;
    options.z = z;
    options.r = 255;
    options.g = 255;
    options.b = 255;
    options.fontpath = DEBUG_FONT;
    options.font_size = fontsize;
    options.text = str;

    draw_text(
        scene->draw_program_text,
        options        
    );

    free(str);

    return size;
}

static size_t draw_debug_fps(float x, float y, float z, int fontsize)
{
    scene_T* scene = application_get_current_scene(APP);

    char* str = calloc(225, sizeof(char));
    sprintf(str, "FPS: %1.6f", APP->fps);
    size_t size = strlen(str);

    draw_options_T options = DRAW_OPTIONS_INIT;
    options.x = x;
    options.y = y + DEBUG_FONT_SIZE;
    options.z = z;
    options.r = 255;
    options.g = 255;
    options.b = 255;
    options.fontpath = DEBUG_FONT;
    options.font_size = fontsize;
    options.text = str;

    draw_text(
        scene->draw_program_text,
        options        
    );

    free(str);

    return size;
}

void debug_draw()
{
    draw_debug_bg(0, 0, DEBUG_Z_INDEX, RES_WIDTH, 32);
    
    const float TEXT_SIZE_MUL = (DEBUG_FONT_SIZE / 2) + (DEBUG_PADDING / 2);
    float x = 0;

    x += draw_debug_dimensions(DEBUG_PADDING + x, (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
    
    x += draw_debug_fps(DEBUG_PADDING + x, (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
    
    x += draw_debug_delta_time(DEBUG_PADDING + x, (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
    
    x += draw_debug_scene_index(DEBUG_PADDING + x, (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
    
    x += draw_debug_nr_actors(DEBUG_PADDING + x, (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
}
