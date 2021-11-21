#version 440

struct Material
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    
    sampler2D diffuse_texture;
    sampler2D specular_texture;
};

in vec3 vs_position;
in vec3 vs_color;
in vec2 vs_texcoord;
in vec3 vs_normal;

out vec4 fs_color;

uniform Material material;

uniform vec3 light_position;
uniform vec3 camera_position;

void main()
{
    // ambient color
    vec4 ambient_color = vec4(material.ambient, 1.f);

    // diffuse color
    vec3 position_to_light_direction = normalize(light_position - vs_position);
    float diffuse = clamp(dot(position_to_light_direction, vs_normal), 0, 1);
    
    vec4 diffuse_color = vec4(material.diffuse * diffuse, 1.f);

    // specular color
    vec3 light_to_position_direction = normalize(vs_position - light_position);
    vec3 light_reflection_direction = normalize(reflect(light_to_position_direction, normalize(vs_normal)));
    vec3 position_to_view_direction = normalize(camera_position - vs_position);
    
    float specular_constant = pow(max(dot(position_to_view_direction, light_reflection_direction), 0), 35);
    vec4 specular_color = vec4(material.specular * specular_constant * texture(material.specular_texture, vs_texcoord).rgb, 1.f);

    fs_color = 
        texture(material.diffuse_texture, vs_texcoord) *
        (ambient_color + diffuse_color + specular_color);
}