#ifndef VERTEX_H_
#define VERTEX_H_

#include <cglm/struct.h>

typedef struct
{
    vec3s position;
    vec3s color;
    vec2s texcoord;
    vec3s normal;
} Vertex;

#endif // VERTEX_H_