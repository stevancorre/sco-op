#include "mesh.h"

void __mesh_init_vertex_array_object(Mesh *mesh, const Model model)
{
    mesh->vertex_count = model.vertex_count;
    mesh->index_count = model.index_count;

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
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * mesh->vertex_count, model.vertices, GL_STATIC_DRAW);

    // generate ebo, bind and send data
    // ebo stands for element buffer object
    // used for vertices indexing
    if (mesh->index_count > 0)
    {
        glGenBuffers(1, &mesh->element_buffer_object);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->element_buffer_object);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Index) * mesh->index_count, model.indices, GL_STATIC_DRAW);
    }

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

void __mesh_init_model_matrix(Mesh *mesh)
{
    mesh_set_position(mesh, GLMS_VEC3_ZERO);
    mesh_set_rotation(mesh, GLMS_VEC3_ZERO);
    mesh_set_scale(mesh, GLMS_VEC3_ONE);

    mesh_update(mesh);
}

Mesh mesh_init(const Model model)
{
    Mesh mesh;

    __mesh_init_vertex_array_object(&mesh, model);
    __mesh_init_model_matrix(&mesh);

    model_free(model);

    return mesh;
}

void mesh_set_position(Mesh *mesh, const vec3s value)
{
    mesh->position = value;
}

void mesh_set_rotation(Mesh *mesh, const vec3s value)
{
    mesh->rotation = value;
}

void mesh_set_scale(Mesh *mesh, const vec3s value)
{
    mesh->scale = value;
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

void mesh_update(Mesh *mesh)
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

void mesh_render(Mesh mesh, Program program)
{
    program_set_mat4fv(program, "model_matrix", mesh.model_matrix, false);

    // bind vao
    glBindVertexArray(mesh.vertex_array_object);

    // draw
    if (mesh.index_count == 0)
    {
        glDrawArrays(GL_TRIANGLES, 0, mesh.vertex_count);
    }
    else
    {
        glDrawElements(GL_TRIANGLES, mesh.index_count, GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
}

void mesh_delete(Mesh *mesh)
{
    glDeleteVertexArrays(1, &mesh->vertex_array_object);
    glDeleteBuffers(1, &mesh->vertex_buffer_object);

    if (mesh->index_count > 0)
    {
        glDeleteBuffers(1, &mesh->element_buffer_object);
    }
}