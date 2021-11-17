#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <errno.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

/**
 * @brief Texture structure
 * 
 */
typedef struct
{
    /**
     * @brief Id of the texture
     * 
     */
    const GLuint id;

    /**
     * @brief The type of the texture
     * 
     */
    const GLenum type;

    /**
     * @brief The texture unit of the texture
     * 
     */
    const GLint texture_unit;

    /**
     * @brief Width of the texture
     * 
     */
    const int width;

    /**
     * @brief Height of the texture
     * 
     */
    const int height;
} Texture;

/**
 * @brief Load a texture from a local file
 * 
 * @param file_path The source file path
 * @param type The desired texture type
 * @return The loaded texture, gl-ready
 */
Texture texture_load(const GLchar* file_path, GLenum type, GLenum texture_unit);

/**
 * @brief Bind a texture
 * 
 * @param texture The target texture
 * @param texture_uint The desired texture unit
 * @param type The desired type
 */
void texture_bind(Texture texture);

/**
 * @brief Unbind a texture
 * 
 * @param texture The target texture
 */
void texture_unbind(Texture texture);

#endif // TEXTURE_H_