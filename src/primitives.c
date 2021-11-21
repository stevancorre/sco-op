#include "model.h"

Model model_init_quad()
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

    // create model
    return model_init(vertices, vertex_count, indices, index_count);
}

Model model_init_triangle()
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

    // create model
    return model_init(vertices, vertex_count, indices, index_count);
}

Model model_init_pyramid()
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

    // create model
    return model_init(vertices, vertex_count, NULL, 0); 
}