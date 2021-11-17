#ifndef PLAYER_H_
#define PLAYER_H_

#include <GLFW/glfw3.h>
#include <cglm/struct.h>
#include "cglm_ext.h"

typedef struct Player
{
    vec3s position;
    vec3s rotation;
    vec3s scale;

    mat4s matrix;
} Player;

void player_init(Player *player);

void player_handle_input(Player *player, GLFWwindow *window);

void player_update_matrix(Player *player);

#endif // PLAYER_H_