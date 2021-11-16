#ifndef SHADERS_H_
#define SHADERS_H_

#include "vertex.h"

#include "slurp_file.h"

/**
 * @brief Gets the specified shader's type as a C string
 * 
 * @param shader The target shader
 * @return The shader's type. Either `fragment`, `vertex` or `unknown`
 */
const char *shader_type_as_cstr(GLuint shader);

/**
 * @brief Compiles a shader from its source
 * 
 * @param source The shader's source code
 * @param shader_type The shader's type
 * @param shader The shader's id
 * @return `true` if the compilation was a success. Otherwise `false`
 */
bool compile_shader_source(const GLchar *source, GLenum shader_type, GLuint *shader);

/**
 * @brief Compiles a shaders from a file
 * 
 * @param file_path The shader's file path
 * @param shader_type The shader's type
 * @param shader The shader's id
 * @return `true` if the compilation was a success. Otherwise `false`
 */
bool compile_shader_file(const char *file_path, GLenum shader_type, GLuint *shader);

/**
 * @brief Attaches the shaders to the program then links it
 * 
 * @param vertex_shader The vertex shader
 * @param fragment_shader The fragment shader
 * @param program The program id
 * @return `true` if the linking was a success. Otherwise `false`
 */
bool link_program(GLuint vertex_shader, GLuint fragment_shader, GLuint *program);

/**
 * @brief Loads a shader program
 * 
 * @param vertex_shader_file_path The vertex shader's path
 * @param fragment_shader_file_path The fragment shader's path
 * @param program The program id
 * @return `true` if the loading was a success. Otherwise `false` 
 */
bool load_shader_program(const char *vertex_shader_file_path, const char *fragment_shader_file_path, GLuint *program);

#endif // SHADERS_H_