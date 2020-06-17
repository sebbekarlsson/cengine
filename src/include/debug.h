#ifndef DEBUG_H
#define DEBUG_H

#define DEBUG_Z_INDEX 5
#define DEBUG_BG_ALPHA 0.9f
#define DEBUG_FONT_SIZE 16
#define DEBUG_FONT "/usr/local/share/cengine/res/fonts/november.ttf"
#define DEBUG_PADDING 4

typedef struct {
    unsigned long size;
    unsigned long resident;
    unsigned long share;
    unsigned long text;
    unsigned long lib;
    unsigned long data;
    unsigned long dt;
} statm_T;

void debug_get_statm(statm_T *result);

unsigned long get_mem_usage();

void debug_tick();

void debug_draw();
#endif
