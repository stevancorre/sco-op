#ifndef GAME_H_
#define GAME_H_

#include "program.h"
#include "player.h"
#include "texture.h"

typedef struct Game
{
    GLFWwindow *window;
    Player player;
} Game;

void game_update_input(Game *game);

#endif // GAME_H_