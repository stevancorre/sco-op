#include "game.h"

void game_update_input(Game *game)
{
    if (glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(game->window, GLFW_TRUE);
    }

    vec3s movement = GLMS_VEC3_ZERO_INIT;
    vec3s rotation = GLMS_VEC3_ZERO_INIT;

    // move
    if (glfwGetKey(game->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        movement.z -= 0.01f;
    }
    if (glfwGetKey(game->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        movement.x -= 0.01f;
    }
    if (glfwGetKey(game->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        movement.z += 0.01f;
    }
    if (glfwGetKey(game->window, GLFW_KEY_D) == GLFW_PRESS)
    {
        movement.x += 0.01f;
    }

    // rotation
    if (glfwGetKey(game->window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        rotation.y -= 1.f;
    }
    if (glfwGetKey(game->window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        rotation.y += 1.f;
    }

    mesh_offset_position(&game->player, movement);
    mesh_offset_rotation(&game->player, rotation);
}