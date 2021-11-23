#ifndef PRIMITIVES_H_
#define PRIMITIVES_H_

#include <GL/glew.h>
#include <memory.h>

#include "vertex.h"

typedef GLuint Index;

typedef struct
{
    Vertex* vertices;
    GLuint vertex_count;

    Index* indices;
    GLuint index_count;
} Primitive;

Primitive primitive_init(
    const Vertex* vertices, const GLuint vertex_count,
    const Index* indices,  const GLuint index_count);

Primitive primitive_init_quad();

Primitive primitive_init_triangle();

Primitive primitive_init_pyramid();

void primitive_free(const Primitive primitive);

#endif