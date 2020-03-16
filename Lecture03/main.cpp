#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include <glm\gtc\matrix_transform.hpp>

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

unsigned const int DELTA_TIME = 10;

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint vao;

GLuint uniform_mvp;
glm::mat4 mvp;
glm::mat4 model;
glm::mat4 view;
glm::mat4 projection;

bool animation = false;
GLfloat scalef = 1.0;
GLfloat xTranslation = 0.0;
GLfloat yTranslation = 0.0;
GLfloat zTranslation = 0.0;
GLfloat xRotation = 0.0;
GLfloat yRotation = 0.0;
GLfloat zRotation = 0.0;

//--------------------------------------------------------------------------------
// Mesh variables
//--------------------------------------------------------------------------------

GLfloat vertices[] = {
    // front
    -1.0, -1.0, 1.0,
    1.0, -1.0, 1.0,
    1.0, 1.0, 1.0,
    -1.0, 1.0, 1.0,
    // back
    -1.0, -1.0, -1.0,
    1.0, -1.0, -1.0,
    1.0, 1.0, -1.0,
    -1.0, 1.0, -1.0
};

GLfloat colors[] = {
    // front colors
    1.0, 1.0, 0.0,
    0.0, 1.0, 0.0,
    0.0, 0.0, 1.0,
    1.0, 1.0, 1.0,
    // back colors
    0.0, 1.0, 1.0,
    1.0, 0.0, 1.0,
    1.0, 0.0, 0.0,
    1.0, 1.0, 0.0
};

GLushort cube_elements[] = {

    0,1,2,
    0,2,3,
    0,5,1,
    0,4,5,
    1,5,2,
    2,5,6,
    0,3,4,
    3,7,4,
    4,6,5,
    4,7,6,
    2,7,3,
    2,6,7
};

//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    switch (key)
    {
    case 27: glutExit(); break; // Esc
    case 70: glutFullScreen(); break; // f
    case 32: animation = !animation; break;

    case '+': model = glm::scale(model, glm::vec3(1.1, 1.1, 1.1)); break; // +
    case '-': model = glm::scale(model, glm::vec3(0.9, 0.9, 0.9)); break; // -

    case 'X': model = glm::rotate(model, glm::radians(1.0f), glm::vec3(1.0, 0.0, 0.0)); break;
    case 'x': model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(1.0, 0.0, 0.0)); break;
    case 'Y': model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0)); break;
    case 'y': model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0.0, 1.0, 0.0)); break;
    case 'Z': model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.0, 0.0, 1.0)); break;
    case 'z': model = glm::rotate(model, glm::radians(-1.0f), glm::vec3(0.0, 0.0, 1.0)); break;
    }
}

void keyboardHandler(int key, int a, int b)
{
    switch (key)
    {
    case GLUT_KEY_UP: model = glm::translate(model, glm::vec3(0.0, 1.0, 0.0)); break; // up arrow
    case GLUT_KEY_DOWN: model = glm::translate(model, glm::vec3(0.0, -1.0, 0.0)); break; // down arrow

    case GLUT_KEY_RIGHT: model = glm::translate(model, glm::vec3(1.0, 0.0, 0.0)); break; // right arrow
    case GLUT_KEY_LEFT: model = glm::translate(model, glm::vec3(-1.0, 0.0, 0.0)); break; // left arrow

    case GLUT_KEY_PAGE_UP: model = glm::translate(model, glm::vec3(0.0, 0.0, 1.0)); break; // PgUp
    case GLUT_KEY_PAGE_DOWN: model = glm::translate(model, glm::vec3(0.0, 0.0, -1.0)); break; //PgDn
    }
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    // Define background
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Attach to program_id
    glUseProgram(program_id);

    glBindVertexArray(vao);
    glDrawElements(
        GL_TRIANGLES,
        sizeof(cube_elements) / sizeof(GLushort),
        GL_UNSIGNED_SHORT,
        (GLvoid*)0);
    glBindVertexArray(0);


    // Swap buffers
    glutSwapBuffers();
}

//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA_TIME, Render, 0);

    if (animation) model = glm::rotate(model, glm::radians(0.5f), glm::vec3(0.0, 1.0, 0.0));

    mvp = projection * view * model;
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(projection * view * model));
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(keyboardHandler);
    glutTimerFunc(DELTA_TIME, Render, 0);

    glewInit();
}


//------------------------------------------------------------
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitShaders()
{
    char* vertexshader = glsl::readFile(vertexshader_name);
    GLuint vsh_id = glsl::makeVertexShader(vertexshader);

    char* fragshader = glsl::readFile(fragshader_name);
    GLuint fsh_id = glsl::makeFragmentShader(fragshader);

    program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
}


//------------------------------------------------------------
// void InitMatrices()
// Initializes the matrices
//------------------------------------------------------------

void InitMatrices()
{
    model = glm::mat4();
    view = glm::lookAt(
        glm::vec3(3.0, 2.0, 5.0),
        glm::vec3(0.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0));
    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20.0f);

    mvp = projection * view * model;
}


//------------------------------------------------------------
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
    GLuint position_id;
    GLuint color_id;
    GLuint vbo_vertices;
    GLuint vbo_colors;
    GLuint ibo_cube_elements;

    // ibo
    glGenBuffers(1, &ibo_cube_elements);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER, sizeof(cube_elements),
        cube_elements, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for colors
    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Get vertex attributes
    position_id = glGetAttribLocation(program_id, "position");
    color_id = glGetAttribLocation(program_id, "color");

    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);

    // Bind vertices to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(position_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Bind colors to vao
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glVertexAttribPointer(color_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(color_id);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Stop bind to vao
    glBindVertexArray(0);

    // make uniform vars
    uniform_mvp = glGetUniformLocation(program_id, "mvp");

    // Fill uniform vars
    glUseProgram(program_id);
    glUniformMatrix4fv(uniform_mvp, 1, GL_FALSE, glm::value_ptr(mvp));
}


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitMatrices();
    InitBuffers();

    glutTimerFunc(DELTA_TIME, Render, 0);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
