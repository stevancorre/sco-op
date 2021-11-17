#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>
#include <cglm/struct.h>

typedef struct Vertex
{
    vec3s position;
    vec3s color;
    vec2s texcoord;
} Vertex;

#endif // VERTEX_H_