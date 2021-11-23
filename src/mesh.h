#ifndef MESH_H_
#define MESH_H_

#include "primitive.h"
#include "shader.h"
#include "material.h"
#include "texture.h"

#define MESH_DEFAULT_INIT GLMS_VEC3_ZERO, GLMS_VEC3_ZERO, GLMS_VEC3_ZERO, GLMS_VEC3_ONE

typedef struct
{
    Primitive primitive;

    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    GLuint element_buffer_object;

    vec3s position;
    vec3s rotation;
    vec3s pivot;
    vec3s scale;

    mat4s model_matrix;
} Mesh;

Mesh mesh_init(const Primitive primitive, const vec3s pivot, const vec3s position, const vec3s rotation, const vec3s scale);

void mesh_set_pivot(Mesh* mesh, const vec3s value);

void mesh_set_position(Mesh *mesh, const vec3s value);

void mesh_set_rotation(Mesh *mesh, const vec3s value);

void mesh_set_scale(Mesh *mesh, const vec3s value);

void mesh_offset_position(Mesh *mesh, const vec3s offset);

void mesh_offset_rotation(Mesh *mesh, const vec3s offset);

void mesh_offset_scale(Mesh *mesh, const vec3s offset);

void mesh_update(Mesh *mesh);

void mesh_render(Mesh mesh, Program program);

void mesh_delete(Mesh *mesh);

#endif // MESH_H_