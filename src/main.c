#include "shaders.h"

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
    GLFWwindow *window;
    GLuint program;

    // initialization
    init_glfw();
    init_window(&window);
    init_glew();
    init_gl();

    load_shader_program("shaders/vertex_core.glsl", "shaders/fragment_core.glsl", &program);

    while (!glfwWindowShouldClose(window))
    {
        //* events
        glfwPollEvents();

        //* update

        //* draw
        // clear
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        // draw

        // end draw
        glfwSwapBuffers(window);
        glFlush();
    }

    // end program
    glfwDestroyWindow(window);
    glfwTerminate();

    glDeleteProgram(program);
    
    return 0;
}