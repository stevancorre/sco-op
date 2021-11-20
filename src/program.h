#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "shader.h"

typedef GLuint Program;

/**
 * @brief Attaches the shaders to the program then links it
 * 
 * @param vertex_shader The vertex shader
 * @param fragment_shader The fragment shader
 * @param program The program id
 * @return `true` if the linking was a success. Otherwise `false`
 */
bool program_link_shader(Program *program, Shader vertex_shader, Shader fragment_shader);

/**
 * @brief Loads a shader program
 * 
 * @param vertex_shader_file_path The vertex shader's path
 * @param fragment_shader_file_path The fragment shader's path
 * @param program The program id
 * @return `true` if the loading was a success. Otherwise `false` 
 */
Program program_load(const GLchar *vertex_shader_file_path, const GLchar *fragment_shader_file_path);

/**
 * @brief Set a specific int uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_1i(Program program, const GLchar *name, GLint value);

/**
 * @brief Set a specific float uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_1f(Program program, const GLchar *name, GLfloat value);

/**
 * @brief Set a specific 2 dimensional float vector uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_vec2fv(Program program, const GLchar *name, vec2s value);

/**
 * @brief Set a specific 3 dimensional float vector uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_vec3fv(Program program, const GLchar *name, vec3s value);

/**
 * @brief Set a specific 4 dimensional float vector uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_vec4fv(Program program, const GLchar *name, vec4s value);

/**
 * @brief Set a specific 3x3 matrix uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_mat3fv(Program program, const GLchar *name, mat3s value, GLboolean transpose);

/**
 * @brief Set a specific 4x4 matrix uniform value for a program
 * 
 * @param program The target program
 * @param name The uniform name
 * @param value The value
 */
void program_set_mat4fv(Program program, const GLchar *name, mat4s value, GLboolean transpose);

/**
 * @brief Use a specified program
 * 
 * @param program The target project
 */
void program_use(Program program);

/**
 * @brief Unuse the current active program
 * 
 */
void program_unuse();

#endif // PROGRAM_H_