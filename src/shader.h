#ifndef SHADERS_H_
#define SHADERS_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/struct.h>

#include "cglm_ext.h"
#include "slurp_file.h"

typedef GLuint Shader;

const GLchar *shader_type_as_cstr(Shader shader);

bool shader_compile_source(Shader *shader, const GLchar *source, GLenum shader_type);

bool shader_compile_source_file(Shader *shader, const GLchar *file_path, GLenum shader_type);

#endif // SHADERS_H_