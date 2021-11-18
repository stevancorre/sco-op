#include "mesh.h"

void __mesh_init_vertex_array_object(Mesh *mesh, Vertex *vertices, const GLuint vertex_count, Index *indices, const GLuint index_count)
{
    mesh->vertex_count = vertex_count;
    mesh->index_count = index_count;

    // generate vao and bind it
    // vao stands for Vertex Array Object
    // it basically holds datas for any renderable object
    glCreateVertexArrays(1, &mesh->vertex_array_object);
    glBindVertexArray(mesh->vertex_array_object);

    // generate vbo, bind and send data
    // vbo stands for Vertex Buffer Object
    // its role is to send the vao's data to the GPU
    // static draw means that we won't edit the size of the object etc
    // in this case, we should GL_DYNAMIC_DRAW
    glCreateBuffers(1, &mesh->vertex_buffer_object);
    glBindBuffer(GL_ARRAY_BUFFER, mesh->vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertex_count, vertices, GL_STATIC_DRAW);

    // generate ebo, bind and send data
    // ebo stands for element buffer object
    // used for vertices indexing
    glGenBuffers(1, &mesh->element_buffer_object);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * mesh->index_count, indices, GL_STATIC_DRAW);

    // set vertex attributes pointers and enable
    // they correspond to the `layout(location = n)` things in the shaders
    // this is how you sort of layout the data you want to send to the shader
    // basically data-indexing

    // color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    // position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    // texcood
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);
    // normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    // unbind
    glBindVertexArray(0);
}

void __mesh_update_uniforms(const Mesh *mesh, Program program)
{
    program_set_mat4fv(program, "model_matrix", mesh->model_matrix, false);
}

void __mesh_update_model_matrix(Mesh *mesh)
{
    mesh->model_matrix = glms_mat4_identity();

    // position
    mesh->model_matrix = glms_translate(mesh->model_matrix, mesh->position);

    // rotation
    mesh->model_matrix = glms_rotate(mesh->model_matrix, glm_rad(mesh->rotation.x), GLMS_VEC3_X);
    mesh->model_matrix = glms_rotate(mesh->model_matrix, glm_rad(mesh->rotation.y), GLMS_VEC3_Y);
    mesh->model_matrix = glms_rotate(mesh->model_matrix, glm_rad(mesh->rotation.z), GLMS_VEC3_Z);

    // scale
    mesh->model_matrix = glms_scale(mesh->model_matrix, mesh->scale);
}

void __mesh_init_model_matrix(Mesh *mesh)
{
    mesh->position = GLMS_VEC3_ZERO;
    mesh->rotation = GLMS_VEC3_ZERO;
    mesh->scale = GLMS_VEC3_ONE;

    __mesh_update_model_matrix(mesh);
}

Mesh mesh_init(const Vertex *vertices, const GLuint vertex_count, const Index *indices, const GLuint index_count)
{
    Mesh mesh;

    __mesh_init_vertex_array_object(&mesh, vertices, vertex_count, indices, index_count);
    __mesh_init_model_matrix(&mesh);

    return mesh;
}

void mesh_set_position(Mesh *mesh, const vec3s value)
{
    mesh->position = value;
}

void mesh_set_rotation(Mesh *mesh, const vec3s value)
{
    mesh->position = value;
}

void mesh_set_scale(Mesh *mesh, const vec3s value)
{
    mesh->position = value;
}

void mesh_offset_position(Mesh *mesh, const vec3s offset)
{
    mesh_set_position(mesh, glms_vec3_add(mesh->position, offset));
}

void mesh_offset_rotation(Mesh *mesh, const vec3s offset)
{
    mesh_set_rotation(mesh, glms_vec3_add(mesh->rotation, offset));
}

void mesh_offset_scale(Mesh *mesh, const vec3s offset)
{
    mesh_set_scale(mesh, glms_vec3_add(mesh->scale, offset));
}

void mesh_render(Mesh *mesh, Program program)
{
    __mesh_update_model_matrix(mesh);
    __mesh_update_uniforms(mesh, program);

    program_use(program);

    // bind vao
    glBindVertexArray(mesh->vertex_array_object);

    // draw
    glDrawElements(GL_TRIANGLES, mesh->index_count, GL_UNSIGNED_INT, 0);
}

void mesh_delete(Mesh *mesh)
{
    glDeleteVertexArrays(1, &mesh->vertex_array_object);
    glDeleteBuffers(1, &mesh->vertex_buffer_object);
    glDeleteBuffers(1, &mesh->element_buffer_object);
}