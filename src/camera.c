#include "camera.h"

Camera camera_init(vec3s position, vec3s forward, vec3s world_up)
{
    (void)forward;
    Camera camera = {
        .world_up = world_up,
        .position = position,

        .pitch = 0,
        .yaw = -90,
        .roll = 0,
        
        .mouse_sensitivity = 7,
        .movement_speed = 2.5};

    camera_update_vectors(&camera);
    camera_update_view_matrix(&camera);

    return camera;
}

void camera_update_vectors(Camera* camera)
{
    camera->forward.x = cos(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    camera->forward.y = sin(glm_rad(camera->pitch));
    camera->forward.z = sin(glm_rad(camera->yaw)) * cos(glm_rad(camera->pitch));
    
    camera->forward = glms_normalize(camera->forward);
    camera->right = glms_normalize(glms_cross(camera->forward, camera->world_up));
    camera->up = glms_normalize(glms_cross(camera->right, camera->forward));
}

void camera_update_view_matrix(Camera *camera)
{
    camera_update_vectors(camera);

    vec3s center = glms_vec3_add(camera->position, camera->forward);
    camera->view_matrix = glms_lookat(camera->position, center, camera->up);
}