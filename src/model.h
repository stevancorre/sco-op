#ifndef MODEL_H_
#define MODEL_H_

#include "primitive.h"
#include "material.h"
#include "mesh.h"

typedef struct
{
    Material material;
    Texture diffuse_texture;
    Texture specular_texture;

    Mesh* meshes;
    GLuint mesh_count;

    vec3s position;
} Model;

Model model_init(
    const vec3s position, 
    const Material material, 
    const Texture diffuse_texture, const Texture specular_texture, 
    const Mesh* meshes, const GLuint mesh_count);

void model_set_position(const Model *model, const vec3s value);

void model_set_rotation(const Model *model, const vec3s value);

void model_set_scale(const Model *model, const vec3s value);

void model_offset_position(const Model *model, const vec3s offset);

void model_offset_rotation(const Model *model, const vec3s offset);

void model_offset_scale(const Model *model, const vec3s offset);

void model_update(const Model* model);

void model_render(const Model model, const Program program);

#endif // MODEL_H_