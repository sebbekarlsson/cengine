#version 330 core
in vec2 fragment_texcoord;
out vec4 color;

uniform sampler2D u_texture;

void main()
{    
    vec4 sampled = vec4(1.0, 1.0, 1.0, texture(u_texture, fragment_texcoord).r);
    color = vec4(vec3(1, 1, 1), 1.0) * sampled;
}
