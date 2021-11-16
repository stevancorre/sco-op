#include "game.h"

void game_update_input(Game* game)
{
    if(glfwGetKey(game->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(game->window, GLFW_TRUE);
    }

    player_handle_input(&game->player, game->window);
}