#ifndef MESH_H_
#define MESH_H_

#include "vertex.h"
#include "shader.h"
#include "material.h"
#include "texture.h"

typedef GLuint Index;

typedef struct
{
    GLuint vertex_count;
    GLuint index_count;

    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    GLuint element_buffer_object;

    vec3s position;
    vec3s rotation;
    vec3s scale;

    mat4s model_matrix;
} Mesh;

Mesh mesh_init(const Vertex *vertices, const GLuint vertex_count, const Index *indices, const GLuint index_count);

void mesh_set_position(Mesh *mesh, const vec3s value);

void mesh_set_rotation(Mesh *mesh, const vec3s value);

void mesh_set_scale(Mesh *mesh, const vec3s value);

void mesh_offset_position(Mesh *mesh, const vec3s offset);

void mesh_offset_rotation(Mesh *mesh, const vec3s offset);

void mesh_offset_scale(Mesh *mesh, const vec3s offset);

void mesh_update(Mesh *mesh);

void mesh_render(Mesh *mesh, Program program);

void mesh_delete(Mesh *mesh);

#endif // MESH_H_