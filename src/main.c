#include "game.h"

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

void init_window(GLFWwindow **window)
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
    GLuint program;

    // initialization
    init_glfw();
    init_window(&game.window);
    init_glew();
    init_gl();

    load_shader_program("shaders/vertex_core.glsl", "shaders/fragment_core.glsl", &program);

    //* BEGIN TEST
    Vertex vertices[] = {
        (Vertex){
            .position = {0, 0.5, 0},
            .color = {1, 0, 0},
            .texcoord = {0, 1}},
        (Vertex){
            .position = {-0.5, -0.5, 0},
            .color = {0, 1, 0},
            .texcoord = {0, 0}},
        (Vertex){
            .position = {0.5, -0.5, 0},
            .color = {0, 0, 1},
            .texcoord = {1, 0}},
    };
    GLuint verticesCount = sizeof(vertices) / sizeof(Vertex);

    GLuint indicies[] = {0, 1, 2};
    GLuint indiciesCount = sizeof(indicies) / sizeof(GLuint);

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
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);  

    // set vertex attributes pointers and enable
    // they correspond to the `layout(location = n)` things in the shaders
    // this is how you sort of layout the data you want to send to the shader
    // basically data-indexing

    // color
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // texcood
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    // bind vao
    glBindVertexArray(vao);

    //* END TEST

    while (!glfwWindowShouldClose(game.window))
    {
        //* events
        glfwPollEvents();

        //* update
        game_update_input(game);

        //* draw
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // use program
        glUseProgram(program);

        // bind vao
        glBindVertexArray(vao);

        // draw
        glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, 0);

        // end draw
        glfwSwapBuffers(game.window);
        glFlush();
    }

    // end program
    glfwDestroyWindow(game.window);
    glfwTerminate();

    glDeleteProgram(program);

    return 0;
}