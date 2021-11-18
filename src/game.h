#ifndef GAME_H_
#define GAME_H_

#include "mesh.h"

typedef struct Game
{
    GLFWwindow *window;
    Mesh player;
} Game;

void game_update_input(Game *game);

#endif // GAME_H_