#ifndef VERTEX_H_
#define VERTEX_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cglm/cglm.h>

#define GLM_VEC2_UP_INIT    {  0.0f,  1.0f }
#define GLM_VEC2_DOWN_INIT  {  0.0f, -1.0f }
#define GLM_VEC2_LEFT_INIT  { -1.0f,  0.0f }
#define GLM_VEC2_RIGHT_INIT {  0.0f,  1.0f }

#define GLM_VEC3_UP_INIT      {  0.0f,  1.0f,  0.0f }
#define GLM_VEC3_DOWN_INIT    {  0.0f, -1.0f,  0.0f }
#define GLM_VEC3_LEFT_INIT    { -1.0f,  0.0f,  0.0f }
#define GLM_VEC3_RIGHT_INIT   {  0.0f,  1.0f,  0.0f }
#define GLM_VEC3_FORWARD_INIT {  0.0f,  0.0f,  1.0f }
#define GLM_VEC3_BACK_INIT    {  0.0f,  0.0f, -1.0f }

#define GLM_VEC2_UP    ((vec2)GLM_VEC2_UP_INIT)
#define GLM_VEC2_DOWN  ((vec2)GLM_VEC2_DOWN_INIT)
#define GLM_VEC2_LEFT  ((vec2)GLM_VEC2_LEFT_INIT)
#define GLM_VEC2_RIGHT ((vec2)GLM_VEC2_RIGHT_INIT) 

#define GLM_VEC3_UP      ((vec3)GLM_VEC2_UP_INIT)
#define GLM_VEC3_DOWN    ((vec3)GLM_VEC2_DOWN_INIT)
#define GLM_VEC3_LEFT    ((vec3)GLM_VEC2_LEFT_INIT)
#define GLM_VEC3_RIGHT   ((vec3)GLM_VEC2_RIGHT_INIT) 
#define GLM_VEC3_FORWARD ((vec3)GLM_VEC3_FORWARD_INIT) 
#define GLM_VEC3_BACK    ((vec3)GLM_VEC3_BACK_INIT) 

typedef struct Vertex {
    vec3 position;
    vec3 color;
    vec2 texcoord;
} Vertex;

#endif // VERTEX_H_