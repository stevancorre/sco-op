#include "program.h"

bool program_link_shader(Program *program, Shader vertex_shader, Shader fragment_shader)
{
    // create, attach the shaders then link the program
    *program = glCreateProgram();

    glAttachShader(*program, vertex_shader);
    glAttachShader(*program, fragment_shader);
    glLinkProgram(*program);

    GLint linked = 0;
    glGetProgramiv(*program, GL_LINK_STATUS, &linked);

    // if the linking failed, get the error and print it to stderr
    if (!linked)
    {
        GLsizei message_size = 0;
        GLchar message[1024];

        glGetProgramInfoLog(*program, sizeof(message), &message_size, message);
        fprintf(stderr, "Program Linking: %.*s\n", message_size, message);
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    return program;
}

bool program_load_shaders(Program *program, const GLchar *vertex_shader_file_path, const GLchar *fragment_shader_file_path)
{
    // load the vertex shader
    Shader vertex_shader = 0;
    if (!shader_compile_source_file(&vertex_shader, vertex_shader_file_path, GL_VERTEX_SHADER))
    {
        return false;
    }

    // load the fragment shader
    Shader fragment_shader = 0;
    if (!shader_compile_source_file(&fragment_shader, fragment_shader_file_path, GL_FRAGMENT_SHADER))
    {
        return false;
    }

    // then link the program
    if (!program_link_shader(program, vertex_shader, fragment_shader))
    {
        return false;
    }

    return true;
}

#define PROGRAM_UNIFORM_LOCATION glGetUniformLocation(program, name)

void program_set_1i(Program program, const GLchar *name, GLint value)
{
    glUniform1i(PROGRAM_UNIFORM_LOCATION, value);
}

void program_set_1f(Program program, const GLchar *name, GLfloat value)
{
    glUniform1f(PROGRAM_UNIFORM_LOCATION, value);
}

void program_set_vec2fv(Program program, const GLchar *name, vec2s value)
{
    glUniform2fv(PROGRAM_UNIFORM_LOCATION, 1, GLMS_VALUE_PTR(value));
}

void program_set_vec3fv(Program program, const GLchar *name, vec3s value)
{
    glUniform3fv(PROGRAM_UNIFORM_LOCATION, 1, GLMS_VALUE_PTR(value));
}

void program_set_vec4fv(Program program, const GLchar *name, vec4s value)
{
    glUniform4fv(PROGRAM_UNIFORM_LOCATION, 1, GLMS_VALUE_PTR(value));
}

void program_set_mat3fv(Program program, const GLchar *name, mat3s value, GLboolean transpose)
{
    glUniformMatrix3fv(PROGRAM_UNIFORM_LOCATION, 1, transpose, GLMS_VALUE_PTR(value));
}

void program_set_mat4fv(Program program, const GLchar *name, mat4s value, GLboolean transpose)
{
    glUniformMatrix4fv(PROGRAM_UNIFORM_LOCATION, 1, transpose, GLMS_VALUE_PTR(value));
}

#undef PROGRAM_ULOC

void program_use(Program program)
{
    glUseProgram(program);
}

void program_unuse()
{
    glUseProgram(0);
}