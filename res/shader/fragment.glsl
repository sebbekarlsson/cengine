#version 330 core
out vec4 FragColor;

in vec2 fragment_texcoord;

in vec4 fragment_color;

flat in int texture_shift_x;
flat in int texture_shift_y;

uniform int atlas_width;
uniform int atlas_height;

uniform sampler2D u_texture;

uniform vec3 world_pos;
uniform vec3 light_pos;

uniform int lighting_enabled;

#define PI 3.1415926535897932384626433832795
#define MAX_DARKNESS 1.95f
#define SHADE_OPACITY 0.003f

void main()
{
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

    vec4 shade = vec4(0, 0, 0, 0);

    if (lighting_enabled == 1)
    {
        vec3 normal = vec3(0, 0, 0);
        vec3 light_vector = vec3(normalize(normal) - light_pos);

        float brightness_mod = 0.0f;
        float dist = distance(world_pos, light_pos);
        float angle = acos(dot(normalize(light_vector), normalize(normal)));
        float darkness = min((smoothstep(0.0, PI / 2.0, angle) * MAX_DARKNESS) + (dist * 0.008), MAX_DARKNESS);

        brightness_mod += 1.0 - darkness;

        shade = vec4(brightness_mod, brightness_mod, brightness_mod, SHADE_OPACITY);
    }

    FragColor = fragment_color * texture2D(u_texture, vec2((fragment_texcoord.x + x) * scalar_x,  (fragment_texcoord.y * scalar_y) + y * scalar_y)) * (vec4(1, 1, 1, 1) + shade);
}
