#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <errno.h>
#include <string.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

typedef struct
{
    const GLuint id;
    const GLenum type;
    const GLint texture_unit;
    const int width;
    const int height;
} Texture;

Texture texture_load(const GLchar *path, GLenum type, GLenum texture_unit);

void texture_bind(Texture texture);

void texture_unbind(Texture texture);

#endif // TEXTURE_H_