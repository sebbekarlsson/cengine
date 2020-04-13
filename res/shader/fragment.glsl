#version 330 core
out vec4 FragColor;
  
in vec2 fragment_texcoord;

uniform sampler2D u_texture;

void main()
{
    FragColor = texture2D(u_texture, fragment_texcoord);
}
