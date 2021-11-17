#ifndef MESH_H_
#define MESH_H_

#include "vertex.h"
#include "shader.h"
#include "material.h"
#include "texture.h"

typedef GLuint Index;

typedef struct
{
    Vertex *vertices;
    GLuint vertex_count;

    Index *indices;
    GLuint index_count;

    GLuint vertex_array_object;
    GLuint vertex_buffer_object;
    GLuint element_buffer_object;

    vec3s position;
    vec3s rotation;
    vec3s scale;

    mat4s model_matrix;
} Mesh;

Mesh mesh_init(Vertex *vertices, const GLuint vertex_count, Index *indices, const GLuint index_count);

void mesh_update(Mesh *mesh);

void mesh_render(Mesh *mesh, Program program);

void mesh_delete(Mesh *mesh);

#endif // MESH_H_