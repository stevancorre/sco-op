#include "model.h"

Model model_init(
    const Vertex *vertices, const GLuint vertex_count,
    const Index *indices, const GLuint index_count)
{
    Model model = {
        .vertices = (Vertex *)malloc(vertex_count * sizeof(Vertex)),
        .vertex_count = vertex_count,
        .indices = (Index *)malloc(index_count * sizeof(Index)),
        .index_count = index_count};

    memcpy(model.vertices, vertices, vertex_count * sizeof(Vertex));
    memcpy(model.indices, indices, index_count * sizeof(Index));

    return model;
}

void model_free(const Model model)
{
    free(model.vertices);
    free(model.indices);
}