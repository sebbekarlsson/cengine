#ifndef CENGINE_SHADER_H
#define CENGINE_SHADER_H
#include <GL/glew.h>

unsigned int init_shader_program_from_file(
    const char* vertex_shader_path,
    const char* fragment_shader_path
);

unsigned int init_shader(GLenum shader_type, const char* src);

unsigned int init_shader_from_file(GLenum shader_type, const char* pathname);

void setup_shaders();
#endif
