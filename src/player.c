#include "player.h"

void player_init(Player *player)
{
    player->position = GLMS_VEC3_ZERO;
    player->rotation = GLMS_VEC3_ZERO;
    player->scale = GLMS_VEC3_ONE;
}

void player_handle_input(Player* player, GLFWwindow* window)
{
    // move
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { player->position.z -= 0.01f; }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { player->position.x -= 0.01f; }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { player->position.z += 0.01f; }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { player->position.x += 0.01f; }

    // rotate
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) { player->rotation.y -= 1; }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { player->rotation.y += 1; }
}

void player_update_matrix(Player* player)
{
    player->matrix = glms_mat4_identity();

    // position
    player->matrix = glms_translate(player->matrix, player->position);

    // rotation
    player->matrix = glms_rotate(player->matrix, glm_rad(player->rotation.x), GLMS_VEC3_X);
    player->matrix = glms_rotate(player->matrix, glm_rad(player->rotation.y), GLMS_VEC3_Y);
    player->matrix = glms_rotate(player->matrix, glm_rad(player->rotation.z), GLMS_VEC3_Z);

    // scale
    player->matrix = glms_scale(player->matrix, player->scale);
}