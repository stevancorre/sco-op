#ifndef MODEL_H_
#define MODEL_H_

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
} Model;

Model model_init(
    const Vertex* vertices, const GLuint vertex_count,
    const Index* indices,  const GLuint index_count);

void model_free(const Model model);

#endif // MODEL_H_