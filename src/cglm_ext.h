#ifndef CGLM_EXT_H_
#define CGLM_EXT_H_

#include <cglm/cglm.h>

#define GLMS_VEC2_UP_INIT    {{  0.0f,  1.0f }}
#define GLMS_VEC2_DOWN_INIT  {{  0.0f, -1.0f }}
#define GLMS_VEC2_LEFT_INIT  {{ -1.0f,  0.0f }}
#define GLMS_VEC2_RIGHT_INIT {{  0.0f,  1.0f }}

#define GLMS_VEC3_UP_INIT      {{  0.0f,  1.0f,  0.0f }}
#define GLMS_VEC3_DOWN_INIT    {{  0.0f, -1.0f,  0.0f }}
#define GLMS_VEC3_LEFT_INIT    {{ -1.0f,  0.0f,  0.0f }}
#define GLMS_VEC3_RIGHT_INIT   {{  0.0f,  1.0f,  0.0f }}
#define GLMS_VEC3_FORWARD_INIT {{  0.0f,  0.0f,  1.0f }}
#define GLMS_VEC3_BACK_INIT    {{  0.0f,  0.0f, -1.0f }}

#define GLMS_VEC2_UP    ((vec2s)GLMS_VEC2_UP_INIT)
#define GLMS_VEC2_DOWN  ((vec2s)GLMS_VEC2_DOWN_INIT)
#define GLMS_VEC2_LEFT  ((vec2s)GLMS_VEC2_LEFT_INIT)
#define GLMS_VEC2_RIGHT ((vec2s)GLMS_VEC2_RIGHT_INIT) 

#define GLMS_VEC3_UP      ((vec3s)GLMS_VEC2_UP_INIT)
#define GLMS_VEC3_DOWN    ((vec3s)GLMS_VEC2_DOWN_INIT)
#define GLMS_VEC3_LEFT    ((vec3s)GLMS_VEC2_LEFT_INIT)
#define GLMS_VEC3_RIGHT   ((vec3s)GLMS_VEC2_RIGHT_INIT) 
#define GLMS_VEC3_FORWARD ((vec3s)GLMS_VEC3_FORWARD_INIT) 
#define GLMS_VEC3_BACK    ((vec3s)GLMS_VEC3_BACK_INIT)

#define GLMS_VEC3_X GLMS_VEC3_RIGHT
#define GLMS_VEC3_Y GLMS_VEC3_UP
#define GLMS_VEC3_Z GLMS_VEC3_FORWARD

#define GLMS_VALUE_PTR(target) (float *)target.raw

#endif // CGLM_EXT_H_