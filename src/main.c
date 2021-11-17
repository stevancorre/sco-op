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

    player_init(&game.player);

    program_load_shaders(&program, "shaders/vertex_core.glsl", "shaders/fragment_core.glsl");

    //* BEGIN TEST
    Vertex vertices[] = {
        (Vertex){
            .position = {{-0.5, 0.5, 0}},
            .color = {{1, 0, 0}},
            .texcoord = {{0, 1}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{-0.5, -0.5, 0}},
            .color = {{0, 1, 0}},
            .texcoord = {{0, 0}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{0.5, -0.5, 0}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}},
            .normal = {{0, 0, 1}}},
        (Vertex){
            .position = {{0.5, 0.5, 0}},
            .color = {{1, 1, 0}},
            .texcoord = {{1, 1}},
            .normal = {{0, 0, 1}}},
    };
    GLuint vertex_count = sizeof(vertices) / sizeof(Vertex);

    GLuint indices[] = {0, 1, 2, 0, 2, 3};
    GLuint index_count = sizeof(indices) / sizeof(GLuint);

    // generate vao and bind it
    // vao stands for Vertex Array Object
    // it basically holds datas for any renderable object
    GLuint vao;
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // generate vbo, bind and send data
    // vbo stands for Vertex Buffer Object
    // its role is to send the vao's data to the GPU
    // static draw means that we won't edit the size of the object etc
    // in this case, we should GL_DYNAMIC_DRAW
    GLuint vbo;
    glCreateBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // generate ebo, bind and send data
    // ebo stands for element buffer object
    // used for vertices indexing
    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attributes pointers and enable
    // they correspond to the `layout(location = n)` things in the shaders
    // this is how you sort of layout the data you want to send to the shader
    // basically data-indexing

    // color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);
    // position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);
    // texcood
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);
    // normal
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, normal));
    glEnableVertexAttribArray(3);

    // bind vao
    // glBindVertexArray(vao);

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
    Mesh mesh = mesh_init(vertices, vertex_count, indices, index_count);

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

    program_set_mat4fv(program, "model", game.player.matrix, GL_FALSE);
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
        player_update_matrix(&game.player);
        program_set_mat4fv(program, "model_matrix", game.player.matrix, GL_FALSE);

        glfwGetFramebufferSize(game.window, &frame_buffer_width, &frame_buffer_height);
        projection_matrix = glms_perspective(glm_rad(fov), (float)frame_buffer_width / frame_buffer_height, nearPlane, farPlane);
        program_set_mat4fv(program, "projection_matrix", projection_matrix, GL_FALSE);

        // activate texture
        // we still need to do that atm, i'll move it a separate function
        // to avoid bind/unbind each time
        texture_bind(texture0);

        glBindVertexArray(vao);

        // draw
        glDrawElements(GL_TRIANGLES, index_count, GL_UNSIGNED_INT, 0);

        // render mesh
        mesh_render(&mesh, program);

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

void mesh_delete(Mesh *mesh)
{
    glDeleteVertexArrays(1, &mesh->vertex_array_object);
    glDeleteBuffers(1, &mesh->vertex_buffer_object);
    glDeleteBuffers(1, &mesh->element_buffer_object);

    free(mesh->indices);
    free(mesh->vertices);
}