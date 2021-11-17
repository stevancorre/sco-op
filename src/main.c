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

    GLuint program;
    int frame_buffer_width = 0;
    int frame_buffer_height = 0;

    // initialization
    init_glfw();
    init_window(&game.window, &frame_buffer_width, &frame_buffer_height);
    init_glew();
    init_gl();

    player_init(&game.player);

    load_shader_program("shaders/vertex_core.glsl", "shaders/fragment_core.glsl", &program);

    //* BEGIN TEST
    Vertex vertices[] = {
        (Vertex){
            .position = {{-0.5, 0.5, 0}},
            .color = {{1, 0, 0}},
            .texcoord = {{0, 1}}},
        (Vertex){
            .position = {{-0.5, -0.5, 0}},
            .color = {{0, 1, 0}},
            .texcoord = {{0, 0}}},
        (Vertex){
            .position = {{0.5, -0.5, 0}},
            .color = {{0, 0, 1}},
            .texcoord = {{1, 0}}},
        (Vertex){
            .position = {{0.5, 0.5, 0}},
            .color = {{1, 1, 0}},
            .texcoord = {{1, 1}}},
    };
    GLuint verticesCount = sizeof(vertices) / sizeof(Vertex);

    GLuint indicies[] = {0, 1, 2, 0, 2, 3};
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, position));
    glEnableVertexAttribArray(0);

    // position
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, color));
    glEnableVertexAttribArray(1);

    // texcood
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texcoord));
    glEnableVertexAttribArray(2);

    // bind vao
    glBindVertexArray(vao);

    // texture unit
    int image_width = 0;
    int image_height = 0;
    stbi_uc *image = stbi_load("assets/64x64.png", &image_width, &image_height, NULL, 4);
    if (image == NULL)
    {
        fprintf(stderr, "ERROR:\tcould not load `assets/64x64.png`: %s\n", strerror(errno));
        exit(1);
    }

    // generate the texId and bind it
    GLuint texture0;
    glGenTextures(1, &texture0);
    glBindTexture(GL_TEXTURE_2D, texture0);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // when we MAGnify the tex (gets bigger)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    // when we MINify the tex (gets smaller)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    // generate a texture by giving its type (tex2d), its format, its size, its border and then its data
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image_width, image_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // mimap are like bigger and smaller versions of the texture
    glGenerateMipmap(GL_TEXTURE_2D);

    // mark the texture as active, bind it as a tex2d and free the pixel data
    glActiveTexture(0);
    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(image);

    // view matrix
    vec3s camPosition = GLMS_VEC3_FORWARD_INIT;
    mat4s view_matrix = glms_lookat(camPosition, glms_vec3_add(camPosition, GLMS_VEC3_BACK), GLMS_VEC3_UP);
    ;

    // projection matrix
    float fov = 90.0f;
    float nearPlane = 0.1f;
    float farPlane = 1000.0f;
    mat4s projection_matrix;

    glUseProgram(program);

    glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, GL_FALSE, (float *)view_matrix.raw);

    glUseProgram(0);

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
        glUseProgram(program);

        // update uniforms
        // texture
        glUniform1i(glGetUniformLocation(program, "texture0"), 0);

        // position, rotation and scale
        player_update_matrix(&game.player);
        glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, GL_FALSE, (float *)game.player.matrix.raw);

        glfwGetFramebufferSize(game.window, &frame_buffer_width, &frame_buffer_height);
        projection_matrix = glms_perspective(glm_rad(fov), (float)frame_buffer_width / frame_buffer_height, nearPlane, farPlane);
        glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, GL_FALSE, (float *)projection_matrix.raw);

        // activate texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture0);

        // bind vao
        glBindVertexArray(vao);

        // draw
        glDrawElements(GL_TRIANGLES, indiciesCount, GL_UNSIGNED_INT, 0);

        // end draw
        glfwSwapBuffers(game.window);
        glFlush();

        // unbind everything
        glBindVertexArray(0);
        glUseProgram(0);
        glActiveTexture(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // end program
    glfwDestroyWindow(game.window);
    glfwTerminate();

    glDeleteProgram(program);

    return 0;
}