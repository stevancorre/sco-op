#version 440

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform sampler2D texture0;
uniform vec3 light_position;
uniform vec3 camera_position;

void main()
{
    // fs_color = vec4(vs_color, 1.f);

    // ambient light
    vec3 ambient_light = vec3(0.1f);

    // diffuse light
    vec3 position_to_light_direction = normalize(vs_position - light_position);
    float diffuse = clamp(dot(position_to_light_direction, vs_normal), 0, 1);
    vec3 diffuse_color = vec3(1.f) * diffuse;

    // specular light
    vec3 light_to_position_direction = normalize(light_position - vs_position);
    vec3 light_reflection_direction = normalize(reflect(light_to_position_direction, normalize(vs_normal)));
    vec3 position_to_view_direction = normalize(vs_position - camera_position);
    float specular_constant = pow(max(dot(position_to_view_direction, light_reflection_direction), 0), 35);
    vec3 specular_light = vec3(1.f) * specular_constant;

    // final light
    fs_color = 
        texture(texture0, vs_texcoord) * vec4(vs_color, 1.f) *
        (vec4(ambient_light, 1.f) + vec4(diffuse_color, 1.f) + vec4(specular_light, 1.
        ));
}