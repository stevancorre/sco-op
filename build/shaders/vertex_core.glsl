#version 440

layout(location = 0) in vec3 vertex_position;
layout(location = 1) in vec3 vertex_color;
layout(location = 2) in vec2 vertex_texcoord;
layout(location = 3) in vec3 vertex_normal;

out vec3 vs_position;
out vec3 vs_color;
out vec2 vs_texcoord;
out vec3 vs_normal;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main()
{
    vs_position = vec4(model_matrix * vec4(vertex_position, 1.f)).xyz;
    vs_color = vertex_color;
    vs_texcoord = vec2(vertex_texcoord.x, -vertex_texcoord.y);
    vs_normal = mat3(model_matrix) * vertex_normal;

    gl_Position = projection_matrix * view_matrix *  model_matrix * vec4(vertex_position, 1.f);
}
