#ifndef GAME_H_
#define GAME_H_

#include "shaders.h"

typedef struct Game {
    GLFWwindow* window;
} Game;

void game_update_input(Game game);

#endif // GAME_H_