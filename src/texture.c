#include "texture.h"

Texture texture_load(const GLchar *path, const GLenum type)
{
    int texture_width = 0;
    int texture_height = 0;
    stbi_uc *image = stbi_load(path, &texture_width, &texture_height, NULL, 4);
    if (image == NULL)
    {
        fprintf(stderr, "ERROR:\tcould not load `%s`: %s\n", path, strerror(errno));
        exit(1);
    }

    // generate the texId and bind it
    GLuint texture_id;
    glGenTextures(1, &texture_id);
    glBindTexture(type, texture_id);

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // when we MAGnify the tex (gets bigger)
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // when we MINify the tex (gets smaller)
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // generate a texture by giving its type (tex2d), its format, its size, its border and then its data
    glTexImage2D(type, 0, GL_RGBA, texture_width, texture_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // mimap are like bigger and smaller versions of the texture
    glGenerateMipmap(type);

    // ubind the texture and free the pixel data
    glActiveTexture(0);
    glBindTexture(type, 0);
    stbi_image_free(image);

    return (Texture){
        .id = texture_id,
        .type = type,
        .width = texture_width,
        .height = texture_height,
    };
}

void texture_bind(const Texture texture, const GLenum texture_unit)
{
    glActiveTexture(texture_unit);
    glBindTexture(texture.type, texture.id);
}

void texture_unbind(const Texture texture)
{
    glActiveTexture(0);
    glBindTexture(texture.type, 0);
}