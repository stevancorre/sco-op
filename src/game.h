#ifndef GAME_H_
#define GAME_H_

#include "mesh.h"
#include "light.h"
#include <memory.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

enum SHADERS
{
    SHADER_STANDARD = 0
};

enum TEXTURES
{
    TEXTURE_64X_PLACEHOLDER = 0,
    TEXTURE_IMG_PLACEHOLDER = 1
};

enum LIGHTS
{
    LIGHT_MAIN = 0
};

enum MESHES
{
    MESH_PLAYER = 0,
    MESH_QUAD = 1,
};

enum MATERIALS
{
    MATERIAL_STANDARD = 0
};

typedef struct Game
{
    GLFWwindow *window;

    // view
    vec3s camera_position;

    mat4s projection_matrix;
    mat4s view_matrix;

    // resources
    Texture *textures;
    GLuint texture_count;

    Program *programs;
    GLuint program_count;

    Material *materials;
    GLuint material_count;

    Mesh *meshes;
    GLuint mesh_count;

    Light *lights;
    GLuint light_count;
} Game;

Game game_init(const GLchar *title, const int window_width, const int window_height, const vec3s camera_position);

bool game_should_close(Game game);

void game_update_input(Game *game);

void game_update(Game *game);

void game_render(Game game);

void game_exit(Game *game, int code);

#endif // GAME_H_