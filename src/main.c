#include "game.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

void terminate_program(int code)
{
    glfwTerminate();
    exit(code);
}

void init_glfw()
{
    // initialize glew
    if (!glfwInit())
    {
        fprintf(stderr, "ERROR:\tcould not initialize GLFW\n");
        exit(1);
    }
}

void init_glew()
{
    // initialize glew
    glewExperimental = GL_TRUE;

    GLenum glew_init_code = glewInit();
    if (glew_init_code != GLEW_OK)
    {
        fprintf(stderr, "ERROR:\tcan't initialize glew\n\t%s\n", glewGetErrorString(glew_init_code));
        terminate_program(1);
    }
}

void frame_buffer_resize_callback(GLFWwindow *window, int width, int height)
{
    (void)window;
    glViewport(0, 0, width, height);
}

void init_window(GLFWwindow **window, int *frame_buffer_width, int *frame_buffer_height)
{
    // initialize window
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    *window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Sco-Op", NULL, NULL);
    if (*window == NULL)
    {
        fprintf(stderr, "ERROR:\tcould not create a window\n");
        terminate_program(1);
    }

    glfwGetFramebufferSize(*window, frame_buffer_width, frame_buffer_height);
    glfwSetFramebufferSizeCallback(*window, frame_buffer_resize_callback);

    // initialize context
    glfwMakeContextCurrent(*window);
}

void init_gl()
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

int main()
{
    Game game;

    Program program;
    int frame_buffer_width = 0;
    int frame_buffer_height = 0;

    // initialization
    init_glfw();
    init_window(&game.window, &frame_buffer_width, &frame_buffer_height);
    init_glew();
    init_gl();

    program_load_shaders(&program, "shaders/vertex_core.glsl", "shaders/fragment_core.glsl");

    //* BEGIN TEST

    // texture
    Texture texture0 = texture_load("assets/64x64.png", GL_TEXTURE_2D, GL_TEXTURE0);

    // material
    Material material0 = {
        .ambient = {{0.1f, 0.1f, 0.1f}},
        .diffuse = GLMS_VEC3_ONE_INIT,
        .specular = GLMS_VEC3_ONE_INIT,
        .diffuse_texture_id = texture0.id,
        .specular_texture_id = texture0.id,
    };

    // mesh
    Model quad = model_init_quad();
    game.player = mesh_init(quad);

    // view matrix
    vec3s camera_position = GLMS_VEC3_FORWARD_INIT;
    mat4s view_matrix = glms_lookat(camera_position, glms_vec3_add(camera_position, GLMS_VEC3_BACK), GLMS_VEC3_UP);

    // lights
    vec3s light_position = GLMS_VEC3_FORWARD_INIT;

    // projection matrix
    float fov = 90.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    glfwGetFramebufferSize(game.window, &frame_buffer_width, &frame_buffer_height);
    mat4s projection_matrix = glms_perspective(glm_rad(fov), (float)frame_buffer_width / frame_buffer_height, nearPlane, farPlane);

    // initialize uniforms
    program_use(program);

    material_send_to_program(material0, program);

    program_set_mat4fv(program, "view_matrix", view_matrix, GL_FALSE);
    program_set_mat4fv(program, "projection_matrix", projection_matrix, GL_FALSE);

    program_set_vec3fv(program, "light_position", light_position);
    program_set_vec3fv(program, "camera_position", camera_position);

    program_unuse();

    //* END TEST

    while (!glfwWindowShouldClose(game.window))
    {
        //* events
        glfwPollEvents();

        //* update
        game_update_input(&game);

        //* draw
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // use program
        program_use(program);

        // update uniforms
        // texture
        //program_set_1i(program, "texture0", 0);

        // position, rotation and scale

        glfwGetFramebufferSize(game.window, &frame_buffer_width, &frame_buffer_height);
        projection_matrix = glms_perspective(glm_rad(fov), (float)frame_buffer_width / frame_buffer_height, nearPlane, farPlane);
        program_set_mat4fv(program, "projection_matrix", projection_matrix, GL_FALSE);

        // activate texture
        // we still need to do that atm, i'll move it a separate function
        // to avoid bind/unbind each time
        texture_bind(texture0);

        // render mesh
        mesh_render(&game.player, program);

        // end draw
        glfwSwapBuffers(game.window);
        glFlush();

        // unbind everything
        glBindVertexArray(0);
        program_unuse();
        texture_unbind(texture0);
    }

    // end program
    glfwDestroyWindow(game.window);
    glfwTerminate();

    glDeleteProgram(program);

    return 0;
}