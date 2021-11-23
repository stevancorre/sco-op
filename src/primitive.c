#include "primitive.h"

Primitive primitive_init(
    const Vertex* vertices, const GLuint vertex_count,
    const Index* indices,  const GLuint index_count)
{

    Primitive primitive = {
        .vertices = (Vertex *)malloc(vertex_count * sizeof(Vertex)),
        .vertex_count = vertex_count,
        .indices = (Index *)malloc(index_count * sizeof(Index)),
        .index_count = index_count};

    memcpy(primitive.vertices, vertices, vertex_count * sizeof(Vertex));
    memcpy(primitive.indices, indices, index_count * sizeof(Index));

    return primitive;
}

Primitive primitive_init_quad()
{
    // initialize data
    const Vertex vertices[] = {
        (Vertex){
            .position = {{-0.5, 0.5, 0}},
            .color = {{1, 0, 0}},
            .texcoord = {{0, 1}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{-0.5, -0.5, 0}},
            .color = {{0, 1, 0}},
            .texcoord = {{0, 0}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{0.5, -0.5, 0}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{0.5, 0.5, 0}},
            .color = {{1, 1, 0}},
            .texcoord = {{1, 1}},
            .normal = {{0, 0, 1}}},
    };
    const GLuint vertex_count = sizeof(vertices) / sizeof(Vertex);

    const GLuint indices[] = {0, 1, 2, 0, 2, 3};
    const GLuint index_count = sizeof(indices) / sizeof(GLuint);

    // create primitive
    return primitive_init(vertices, vertex_count, indices, index_count);
}

Primitive primitive_init_triangle()
{
    // initialize data
    const Vertex vertices[] = {
        (Vertex){
            .position = {{-0.5, 0.5, 0}},
            .color = {{1, 0, 0}},
            .texcoord = {{0, 1}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{-0.5, -0.5, 0}},
            .color = {{0, 1, 0}},
            .texcoord = {{0, 0}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{0.5, -0.5, 0}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{0, 0, 1}}},
    };
    const GLuint vertex_count = sizeof(vertices) / sizeof(Vertex);

    const GLuint indices[] = {0, 1, 2};
    const GLuint index_count = sizeof(indices) / sizeof(GLuint);

    // create primitive
    return primitive_init(vertices, vertex_count, indices, index_count);
}

Primitive primitive_init_pyramid()
{
    // initialize data
    const Vertex vertices[] = {
        // front
        (Vertex){
            .position = {{0, 0.5, 0}},
            .color = {{1, 0, 0}},
            .texcoord = {{0.5, 1}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{-0.5, -0.5, 0.5}},
            .color = {{0, 1, 0}},
            .texcoord = {{0, 0}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{0.5, -0.5, 0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{0, 0, 1}}},
        
        // left
        (Vertex){
            .position = {{0, 0.5, 0}},
            .color = {{1, 1, 0}},
            .texcoord = {{0.5, 1}},
            .normal = {{-1, 0, 0}}},
        (Vertex){
            .position = {{-0.5, -0.5, -0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{0, 0}},
            .normal = {{-1, 0, 0}}},
        (Vertex){
            .position = {{-0.5, -0.5, 0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{-1, 0, 0}}},

        // back
        (Vertex){
            .position = {{0, 0.5, 0}},
            .color = {{1, 1, 0}},
            .texcoord = {{0.5, 1}},
            .normal = {{0, 0, -1}}},
        (Vertex){
            .position = {{0.5, -0.5, -0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{0, 0}},
            .normal = {{0, 0, -1}}},
        (Vertex){
            .position = {{-0.5, -0.5, -0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{0, 0, -1}}},

        // right
        (Vertex){
            .position = {{0, 0.5, 0}},
            .color = {{1, 1, 0}},
            .texcoord = {{0.5, 1}},
            .normal = {{1, 0, 0}}},
        (Vertex){
            .position = {{0.5, -0.5, 0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{0, 0}},
            .normal = {{1, 0, 0}}},
        (Vertex){
            .position = {{0.5, -0.5, -0.5}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{1, 0, 0}}},
    };
    const GLuint vertex_count = sizeof(vertices) / sizeof(Vertex);

    // create primitive
    return primitive_init(vertices, vertex_count, NULL, 0); 
}

void primitive_free(const Primitive primitive)
{
    free(primitive.vertices);
    free(primitive.indices);
}