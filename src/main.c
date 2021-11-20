#include "game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main()
{
    // initialization
    Game game = game_init("Sco-Op", WINDOW_WIDTH, WINDOW_HEIGHT, GLMS_VEC3_FORWARD);

    while (!game_should_close(game))
    {
        game_update_input(&game);
        game_update(&game);
        game_render(game);
    }

    game_exit(&game, 0);
}