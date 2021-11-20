#ifndef PROGRAM_H_
#define PROGRAM_H_

#include "shader.h"

typedef GLuint Program;

bool program_link_shader(Program *program, Shader vertex_shader, Shader fragment_shader);

Program program_load(const GLchar *vertex_shader_file_path, const GLchar *fragment_shader_file_path);

void program_set_1i(Program program, const GLchar *name, GLint value);

void program_set_1f(Program program, const GLchar *name, GLfloat value);

void program_set_vec2fv(Program program, const GLchar *name, vec2s value);

void program_set_vec3fv(Program program, const GLchar *name, vec3s value);

void program_set_vec4fv(Program program, const GLchar *name, vec4s value);

void program_set_mat3fv(Program program, const GLchar *name, mat3s value, GLboolean transpose);

void program_set_mat4fv(Program program, const GLchar *name, mat4s value, GLboolean transpose);

void program_use(Program program);

void program_unuse();

#endif // PROGRAM_H_