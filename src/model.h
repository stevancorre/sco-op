#ifndef MODEL_H_
#define MODEL_H_

#include "primitive.h"
#include "material.h"
#include "mesh.h"

typedef struct
{
    Material* material;
    Texture* diffuse_texture;
    Texture* specular_texture;

    Mesh** meshes;
    GLuint mesh_count;

    vec3s position;
} Model;

#endif // MODEL_H_