#include "shaders.h"

const char *shader_type_as_cstr(GLuint shader)
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

bool compile_shader_source(const GLchar *source, GLenum shader_type, GLuint *shader)
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

bool compile_shader_file(const char *file_path, GLenum shader_type, GLuint *shader)
{
    // load the source from the specified path, then compile it
    char *source = slurp_file(file_path);
    bool ok = compile_shader_source(source, shader_type, shader);
    
    // if the compilation fails, print it to stderr
    if (!ok)
    {
        fprintf(stderr, "ERROR: failed to compile `%s` shader file\n", file_path);
    }

    free(source);
    return ok;
}

bool link_program(GLuint vertex_shader, GLuint fragex_shader, GLuint *program)
{
    // create, attach the shaders then link the program
    *program = glCreateProgram();

    glAttachShader(*program, vertex_shader);
    glAttachShader(*program, fragex_shader);
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
    glDeleteShader(fragex_shader);

    return program;
}

bool load_shader_program(const char *vertex_shader_file_path, const char *fragment_shader_file_path, GLuint *program)
{
    // load the vertex shader
    GLuint vertex_shader = 0;
    if (!compile_shader_file(vertex_shader_file_path, GL_VERTEX_SHADER, &vertex_shader))
    {
        return false;
    }

    // load the fragment shader
    GLuint fragment_shader = 0;
    if (!compile_shader_file(fragment_shader_file_path, GL_FRAGMENT_SHADER, &fragment_shader))
    {
        return false;
    }

    // then link the program
    if (!link_program(vertex_shader, fragment_shader, program))
    {
        return false;
    }

    return true;
}