#include "include/shader.h"
#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>

extern volatile unsigned int SHADER_PROGRAM;


unsigned int init_shader_program_from_file(
    const char* vertex_shader_path,
    const char* fragment_shader_path
)
{
    unsigned int vertex_shader = init_shader_from_file(
        GL_VERTEX_SHADER,
        vertex_shader_path
    );

    unsigned int fragment_shader = init_shader_from_file(
        GL_FRAGMENT_SHADER,
        fragment_shader_path
    );

    unsigned int program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    return program;
}

unsigned int init_shader(GLenum shader_type, const char* src)
{
    int success;
    char infoLog[512];

    unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &src, NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        printf("ERROR:%s\n", src);
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        perror(infoLog);
    }

    return shader;
}

unsigned int init_shader_from_file(GLenum shader_type, const char* pathname)
{
    char* source = read_file(pathname);
    unsigned int shader = init_shader(shader_type, source);
    free(source);

    return shader;
}
