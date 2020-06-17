#include "include/debug.h"
#include "include/draw.h"
#include "include/application.h"
#include <string.h>
#include <errno.h>
#include <sys/resource.h>


extern application_T* APP;

void debug_get_statm(statm_T* result)
{
  const char* statm_path = "/proc/self/statm";

  FILE *f = fopen(statm_path, "r");

  if(!f)
  {
      perror(statm_path);
      abort();
  }

  if(fscanf(
      f,
      "%ld %ld %ld %ld %ld %ld %ld",
      &result->size,
      &result->resident,
      &result->share,
      &result->text,
      &result->lib,
      &result->data,
      &result->dt
  ) != 7)
  {
    perror(statm_path);
    abort();
  }

  fclose(f);
}

unsigned long get_mem_usage()
{
    struct rusage r_usage;

    int ret = getrusage(RUSAGE_SELF,&r_usage);

    if(ret != 0)
        printf("Error in getrusage. errno = %d\n", errno);

   return r_usage.ru_maxrss;
}

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

static size_t draw_debug_general(float x, float y, float z, int fontsize)
{
    scene_T* scene = application_get_current_scene(APP);

    const char* template = "(%dD) | FPS: %1.2f | scene: %d | actors: %d | delta: %1.4f";
    char* str = calloc(strlen(template) + 428, sizeof(char));
    sprintf(str, template, scene->camera->dimensions, APP->fps, APP->scene_index, (int) scene->actors->size, APP->delta_time);
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

static size_t draw_debug_memory_usage(float x, float y, float z, int fontsize)
{
    scene_T* scene = application_get_current_scene(APP);

    statm_T stats = {};
    debug_get_statm(&stats);

    unsigned long int mem_usage = get_mem_usage();

    const char* template = "Mem: %ld KB | size: %ld | resident: %ld | data: %ld | text: %ld";
    char* str = calloc(strlen(template) + 428, sizeof(char));
    sprintf(str, template, mem_usage, stats.size, stats.resident, stats.data, stats.text);
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
    draw_debug_bg(0, 0, DEBUG_Z_INDEX, RES_WIDTH, 64);
    
    const float TEXT_SIZE_MUL = (DEBUG_FONT_SIZE / 2) + (DEBUG_PADDING / 2);
    float x = 0;
    float y = 0;

    x += draw_debug_general(DEBUG_PADDING + x, y + (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
    
    y += 32; 
    x = 0;
    
    x += draw_debug_memory_usage(DEBUG_PADDING + x, y + (32 / 2) - DEBUG_FONT_SIZE / 2, DEBUG_Z_INDEX + 1, DEBUG_FONT_SIZE) * TEXT_SIZE_MUL;
}
