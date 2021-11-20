#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "program.h"

typedef vec3s Color;
typedef GLint TextureId;

typedef struct {
    Color ambient;
    Color diffuse;
    Color specular;
    
    TextureId diffuse_texture_id;
    TextureId specular_texture_id;
} Material;

void material_send_to_program(Material material, Program program);

#endif // MATERIAL_H_