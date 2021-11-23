#include "model.h"

Model model_init(
    const vec3s position,
    const Material material,
    const Texture diffuse_texture, const Texture specular_texture,
    const Mesh *meshes, const GLuint mesh_count)
{
    Model model = {
        .position = position,
        .material = material,
        .diffuse_texture = diffuse_texture,
        .specular_texture = specular_texture,
        .meshes = (Mesh *)malloc(mesh_count * sizeof(Mesh)),
        .mesh_count = mesh_count};
    memcpy(model.meshes, meshes, mesh_count * sizeof(Mesh));

    return model;
}

void model_render(const Model model, const Program program)
{
    // bind
    material_send_to_program(model.material, program);

    texture_bind(model.diffuse_texture, GL_TEXTURE0);
    texture_bind(model.specular_texture, GL_TEXTURE1);

    // render
    for (GLuint i = 0; i < model.mesh_count; i++)
    {
        mesh_render(model.meshes[i], program);
    }

    // unbind
    texture_unbind(model.diffuse_texture);
    texture_unbind(model.specular_texture);
}