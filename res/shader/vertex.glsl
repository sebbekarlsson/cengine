#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texcoord;
layout (location = 3) in float in_texture_shift_x;
layout (location = 4) in float in_texture_shift_y;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 fragment_texcoord;

flat out int texture_shift_x;
flat out int texture_shift_y;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0);
    fragment_texcoord = texcoord;

    texture_shift_x = int(ceil(in_texture_shift_x));
    texture_shift_y = int(ceil(in_texture_shift_y));
}
