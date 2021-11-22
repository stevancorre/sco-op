#ifndef CAMERA_H_
#define CAMERA_H_

#include <cglm/struct.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "cglm_ext.h"

typedef struct
{
    vec3s world_up;

    vec3s position;
    vec3s forward;
    vec3s right;
    vec3s up;

    GLfloat pitch;
    GLfloat yaw;
    GLfloat roll;

    GLfloat mouse_sensitivity;
    GLfloat movement_speed;

    mat4s view_matrix;
} Camera;

Camera camera_init(vec3s position, vec3s forward, vec3s world_up);

void camera_update_vectors(Camera* camera);

void camera_update_view_matrix(Camera* camera);

#endif // CAMERA_H_