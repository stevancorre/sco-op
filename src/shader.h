#ifndef SHADERS_H_
#define SHADERS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#include "vertex.h"
#include "cglm_ext.h"
#include "slurp_file.h"

#define UNIFORM_INT(name, value) glGetUniformLocation(program, name), value
#define UNIFORM_VEC(name, value) glGetUniformLocation(program, name), 1, GLMS_VALUE_PTR(value)
#define UNIFORM_MAT(name, value, transpose) glGetUniformLocation(program, name), 1, transpose, GLMS_VALUE_PTR(value)

typedef GLuint Shader;
typedef GLuint Program;

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

/**
 * @brief Attaches the shaders to the program then links it
 * 
 * @param vertex_shader The vertex shader
 * @param fragment_shader The fragment shader
 * @param program The program id
 * @return `true` if the linking was a success. Otherwise `false`
 */
bool shader_link_program(Program *program, Shader vertex_shader, Shader fragment_shader);

/**
 * @brief Loads a shader program
 * 
 * @param vertex_shader_file_path The vertex shader's path
 * @param fragment_shader_file_path The fragment shader's path
 * @param program The program id
 * @return `true` if the loading was a success. Otherwise `false` 
 */
bool shader_load_program(Program *program, const GLchar *vertex_shader_file_path, const GLchar *fragment_shader_file_path);

#endif // SHADERS_H_