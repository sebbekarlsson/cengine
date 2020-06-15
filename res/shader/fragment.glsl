#version 330 core

/** CONSTANTS **/
#define PI 3.1415926535897932384626433832795
const int MAX_LIGHTS = 128;

out vec4 FragColor;

in vec2 fragment_texcoord;

in vec4 fragment_color;

flat in int texture_shift_x;
flat in int texture_shift_y;

uniform int atlas_width;
uniform int atlas_height;

uniform float pan_x;
uniform float pan_y;

uniform sampler2D u_texture;

uniform vec3 world_pos;
uniform int nr_lights = 1;
uniform vec3 light_pos[MAX_LIGHTS];

uniform int lighting_enabled = 0;
uniform float lighting_max_darkness = 1.95f;
uniform float lighting_shade_opacity = 0.003f;

uniform float time;

void main()
{
    float MAX_DARKNESS = lighting_max_darkness;
    float SHADE_OPACITY = lighting_shade_opacity; 

    int width = atlas_width;

    if (width == 0)
        width += 1;

    int height = atlas_height;

    if (height == 0)
        height += 1;

    int x = texture_shift_x;
    int y = texture_shift_y;

    float scalar_x = 1.0 / width;
    float scalar_y = 1.0 / height;
    
    float brightness_mod = lighting_shade_opacity;

    if (lighting_enabled == 1)
    {
        for (int i = 0; i < nr_lights; i++)
        {
            vec3 normal = vec3(0, 0, 0);
            vec3 light_vector = vec3(normalize(normal) - light_pos[i]);

            float dist = distance(world_pos, light_pos[i]);
            float angle = acos(dot(normalize(light_vector), normalize(normal)));
            float darkness = min((smoothstep(0.0, PI / 2.0, angle) * MAX_DARKNESS) + (dist * 0.008), MAX_DARKNESS);

            brightness_mod += 1.0 - darkness;
            brightness_mod = min(1, brightness_mod);
        }
    }
    
    vec4 shade = vec4(brightness_mod, brightness_mod, brightness_mod, SHADE_OPACITY);

    float tex_x = (fragment_texcoord.x + x) * scalar_x;
    float tex_y = (fragment_texcoord.y * scalar_y) + y * scalar_y;

    vec2 texture_pos = vec2(tex_x + pan_x, tex_y + pan_y);

    vec4 new_shade = vec4(min(1, 1 + shade.r), min(1, 1 + shade.g), min(1, 1 + shade.b), min(1, 1 + shade.a));

    FragColor = fragment_color * texture2D(u_texture, texture_pos) * new_shade;
}
