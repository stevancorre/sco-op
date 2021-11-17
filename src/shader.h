#ifndef SHADERS_H_
#define SHADERS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "vertex.h"
#include "cglm_ext.h"
#include "slurp_file.h"

typedef GLuint Shader;

/**
 * @brief Gets the specified shader's type as a C string
 * 
 * @param shader The target shader
 * @return The shader's type. Either `fragment`, `vertex` or `unknown`
 */
const GLchar *shader_type_as_cstr(Shader shader);

/**
 * @brief Compiles a shader from its source
 * 
 * @param source The shader's source code
 * @param shader_type The shader's type
 * @param shader The shader's id
 * @return `true` if the compilation was a success. Otherwise `false`
 */
bool shader_compile_source(Shader *shader, const GLchar *source, GLenum shader_type);

/**
 * @brief Compiles a shaders from a file
 * 
 * @param file_path The shader's file path
 * @param shader_type The shader's type
 * @param shader The shader's id
 * @return `true` if the compilation was a success. Otherwise `false`
 */
bool shader_compile_source_file(Shader *shader, const GLchar *file_path, GLenum shader_type);

#endif // SHADERS_H_