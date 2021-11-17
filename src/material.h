#ifndef MATERIAL_H_
#define MATERIAL_H_

#include "program.h"

typedef vec3s Color;
typedef GLint TextureId;

/**
 * @brief Material struct
 * 
 */
typedef struct {
    /**
     * @brief The ambient color
     * 
     */
    Color ambient;

    /**
     * @brief The diffuse color
     * 
     */
    Color diffuse;

    /**
     * @brief The specular color
     * 
     */
    Color specular;

    /**
     * @brief The diffuse texture id (GLint)
     * 
     */
    TextureId diffuse_texture_id;

    /**
     * @brief The diffuse texture id (GLint)
     * 
     */
    TextureId specular_texture_id;
} Material;

/**
 * @brief Send a material data to a shader program
 * 
 * @param material The material
 * @param program The target program
 */
void material_send_to_program(Material material, Program program);

#endif // MATERIAL_H_