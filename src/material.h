#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "program.h"

typedef vec3s Color;

typedef struct {
    Color ambient;
    Color diffuse;
    Color specular;
    
    GLenum diffuse_texture;
    GLenum specular_texture;
} Material;

void material_send_to_program(Material material, Program program);

#endif // MATERIAL_H_