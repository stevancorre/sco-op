#include "game.h"

static void __frame_buffer_resize_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

static void __init_glfw()
{
    // initialize glew
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR:\tcould not initialize GLFW\n");
        exit(1);
    }
}

static void __game_init_window(Game *game, const GLchar *title, const int window_width, const int window_height)
{
    // initialize window
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    game->window = glfwCreateWindow(window_width, window_height, title, NULL, NULL);
    if (game->window == NULL)
    {
        fprintf(stderr, "ERROR:\tcould not create a window\n");
        game_exit(game, 1);
    }

    // window resize callback
    glfwSetFramebufferSizeCallback(game->window, __frame_buffer_resize_callback);

    // initialize context
    glfwMakeContextCurrent(game->window);
}

static void __init_glew(Game *game)
{
    // initialize glew
    glewExperimental = GL_TRUE;

    GLenum glew_init_code = glewInit();
    if (glew_init_code != GLEW_OK)
    {
        fprintf(stderr, "ERROR:\tcan't initialize glew\n\t%s\n", glewGetErrorString(glew_init_code));
        game_exit(game, 1);
    }
}

static void __init_gl()
{
    // opengl options
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

static void __game_init_textures(Game *game)
{
    const Texture textures[] = {
        [TEXTURE_64X_PLACEHOLDER] = texture_load("assets/64x64.png", GL_TEXTURE_2D),
        [TEXTURE_IMG_PLACEHOLDER] = texture_load("assets/placeholder.png", GL_TEXTURE_2D)};

    game->texture_count = sizeof(textures) / sizeof(Texture);
    game->textures = (Texture *)malloc(game->texture_count * sizeof(Texture));
    memcpy(game->textures, textures, game->texture_count * sizeof(Texture));
}

static void __game_init_shader_programs(Game *game)
{
    const Program programs[] = {
        [SHADER_STANDARD] = program_load("shaders/vertex_core.glsl", "shaders/fragment_core.glsl")};

    game->program_count = sizeof(programs) / sizeof(Program);
    game->programs = (Program *)malloc(game->program_count * sizeof(Program));

    memcpy(game->programs, programs, game->program_count * sizeof(Program));
}

static void __game_init_materials(Game *game)
{
    const Material materials[] = {
        [SHADER_STANDARD] = {
            .ambient = {{0.1f, 0.1f, 0.1f}},
            .diffuse = GLMS_VEC3_ONE_INIT,
            .specular = GLMS_VEC3_ONE_INIT,
            .diffuse_texture = GL_TEXTURE0,
            .specular_texture = GL_TEXTURE0,
        }};

    game->material_count = sizeof(materials) / sizeof(Material);
    game->materials = (Material *)malloc(game->material_count * sizeof(Material));
    memcpy(game->materials, materials, game->material_count * sizeof(Material));

    program_use(game->programs[SHADER_STANDARD]);
    material_send_to_program(game->materials[SHADER_STANDARD], game->programs[SHADER_STANDARD]);
    program_unuse();
}

static void __game_init_meshes(Game *game)
{
    const Mesh meshes[] = {
        [MESH_PLAYER] = mesh_init(model_init_quad()),
        [MESH_QUAD] = mesh_init(model_init_quad())};

    game->mesh_count = sizeof(meshes) / sizeof(Mesh);
    game->meshes = (Mesh *)malloc(game->mesh_count * sizeof(Mesh));
    memcpy(game->meshes, meshes, game->mesh_count * sizeof(Mesh));
}

static void __game_init_lights(Game *game)
{
    const Light lights[] = {
        [LIGHT_MAIN] = GLMS_VEC3_FORWARD};

    game->light_count = sizeof(lights) / sizeof(Light);
    game->lights = (Light *)malloc(game->light_count * sizeof(Light));
    memcpy(game->lights, lights, game->light_count * sizeof(Light));
}

static void __game_init_uniforms(const Game *game)
{
    program_use(game->programs[SHADER_STANDARD]);

    program_set_mat4fv(game->programs[SHADER_STANDARD], "view_matrix", game->view_matrix, GL_FALSE);
    program_set_mat4fv(game->programs[SHADER_STANDARD], "projection_matrix", game->projection_matrix, GL_FALSE);

    program_set_vec3fv(game->programs[SHADER_STANDARD], "light_position", game->lights[LIGHT_MAIN]);
    program_set_vec3fv(game->programs[SHADER_STANDARD], "camera_position", game->camera_position);

    program_unuse();
}

static void __game_update_camera(Game *game)
{
    // projection
    float fov = 90.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;

    int frame_buffer_width = 0;
    int frame_buffer_height = 0;
    glfwGetFramebufferSize(game->window, &frame_buffer_width, &frame_buffer_height);
    game->projection_matrix = glms_perspective(glm_rad(fov), (float)frame_buffer_width / frame_buffer_height, nearPlane, farPlane);

    // view
    vec3s camera_forward = GLMS_VEC3_BACK_INIT;
    game->view_matrix = glms_lookat(game->camera_position, glms_vec3_add(game->camera_position, camera_forward), GLMS_VEC3_UP);
}

static void __game_update_uniforms(Game game)
{
    program_use(game.programs[SHADER_STANDARD]);

    program_set_mat4fv(game.programs[SHADER_STANDARD], "view_matrix", game.view_matrix, GL_FALSE);
    program_set_mat4fv(game.programs[SHADER_STANDARD], "projection_matrix", game.projection_matrix, GL_FALSE);
    program_set_vec3fv(game.programs[SHADER_STANDARD], "camera_position", game.camera_position);
    
    program_unuse();
}

Game game_init(const GLchar *title, const int window_width, const int window_height, const vec3s camera_position)
{
    Game game = {
        .camera_position = camera_position};

    __init_glfw();
    __game_init_window(&game, title, window_width, window_height);

    __init_glew(&game);
    __init_gl();

    // resources
    __game_init_shader_programs(&game);
    __game_init_textures(&game);
    __game_init_materials(&game);
    __game_init_meshes(&game);
    __game_init_lights(&game);

    __game_update_camera(&game);

    __game_init_uniforms(&game);

    return game;
}

bool game_should_close(Game game)
{
    return glfwWindowShouldClose(game.window);
}

void game_update_input(Game *game)
{
    glfwPollEvents();

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

    mesh_offset_position(&game->meshes[MESH_PLAYER], movement);
    mesh_offset_rotation(&game->meshes[MESH_PLAYER], rotation);
}

void game_update(Game *game)
{
    __game_update_camera(game);
    mesh_update(&game->meshes[MESH_PLAYER]);
    mesh_update(&game->meshes[MESH_QUAD]);
}

void game_render(Game game)
{
    // clear
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // bind shaders and textures

    // update uniforms
    __game_update_uniforms(game);

    // render stuff
    program_use(game.programs[SHADER_STANDARD]);

    texture_bind(game.textures[TEXTURE_64X_PLACEHOLDER], GL_TEXTURE0);
    mesh_render(game.meshes[MESH_PLAYER], game.programs[SHADER_STANDARD]);

    texture_bind(game.textures[TEXTURE_IMG_PLACEHOLDER], GL_TEXTURE0);
    mesh_render(game.meshes[MESH_QUAD], game.programs[SHADER_STANDARD]);

    // unbind everything
    program_unuse();
    texture_unbind(game.textures[TEXTURE_64X_PLACEHOLDER]);
    texture_unbind(game.textures[TEXTURE_IMG_PLACEHOLDER]);

    // end draw
    glfwSwapBuffers(game.window);
    glFlush();
}

void game_exit(Game *game, int code)
{
    glfwDestroyWindow(game->window);
    glfwTerminate();

    free(game->textures);
    free(game->programs);
    free(game->materials);

    exit(code);
}