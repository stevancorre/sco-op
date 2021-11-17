#include "shader.h"

const GLchar *shader_type_as_cstr(Shader shader)
{
    switch (shader)
    {
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    default:
        return "(Unknown)";
    }
}

bool shader_compile_source(Shader *shader, const GLchar *source, GLenum shader_type)
{
    // try to compile the shader
    *shader = glCreateShader(shader_type);
    glShaderSource(*shader, 1, &source, NULL);
    glCompileShader(*shader);

    GLint compiled = 0;
    glGetShaderiv(*shader, GL_COMPILE_STATUS, &compiled);

    // if it fails, get the error then print it to stderr
    if (!compiled)
    {
        GLchar message[1024];
        GLsizei message_size = 0;

        glGetShaderInfoLog(*shader, sizeof(message), &message_size, message);

        fprintf(stderr, "ERROR: could not compile %s\n", shader_type_as_cstr(shader_type));
        fprintf(stderr, "%.*s\n", message_size, message);
        return false;
    }

    return true;
}

bool shader_compile_source_file(Shader *shader, const GLchar *file_path, GLenum shader_type)
{
    // load the source from the specified path, then compile it
    char *source = slurp_file(file_path);
    bool ok = shader_compile_source(shader, source, shader_type);

    // if the compilation fails, print it to stderr
    if (!ok)
    {
        fprintf(stderr, "ERROR: failed to compile `%s` shader file\n", file_path);
    }

    free(source);
    return ok;
}

bool shader_link_program(Program *program, Shader vertex_shader, Shader fragment_shader)
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

bool shader_load_program(Program *program, const GLchar *vertex_shader_file_path, const GLchar *fragment_shader_file_path)
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
    if (!shader_link_program(program, vertex_shader, fragment_shader))
    {
        return false;
    }

    return true;
}