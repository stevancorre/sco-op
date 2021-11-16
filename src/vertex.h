#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

typedef struct Vertex {
    vec3 position;
    vec3 color;
    vec2 texcoord;
} Vertex;

#endif // VERTEX_H_