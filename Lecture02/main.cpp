#include <iostream>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "glsl.h"

using namespace std;


//--------------------------------------------------------------------------------
// Structs
//--------------------------------------------------------------------------------

struct VertexFormat
{
    glm::vec4 position;
    glm::vec4 color;
    VertexFormat(glm::vec4 pos, glm::vec4 col)
    {
        position = pos;
        color = col;
    }
};


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int DELTA = 10;
const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

// Mesh variables
/*
VertexFormat tri[] = {
   VertexFormat(glm::vec4(0.5, -0.5, 0.0, 1.0),
                glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),
   VertexFormat(glm::vec4(-0.5, -0.5, 0.0, 1.0),
                glm::vec4(0.0f, 1.0f, 0.0f, 1.0f)),
   VertexFormat(glm::vec4(0.0, 0.5, 0.0, 1.0),
                glm::vec4(0.0f, 0.0f, 1.0f, 1.0f))
};
*/

VertexFormat star[] = {
    VertexFormat(glm::vec4(0.0, -0.4, 0.0, 1.0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(0.1, -0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(0.2, -0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(0.2, -0.1, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(0.4, 0.0, 0.0, 1.0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(0.2, 0.1, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(0.2, 0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(0.1, 0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(0.0, 0.4, 0.0, 1.0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(-0.1, 0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(-0.2, 0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(-0.2, 0.1, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(-0.4, 0.0, 0.0, 1.0), glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)),

    VertexFormat(glm::vec4(-0.2, -0.1, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(-0.2, -0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
    VertexFormat(glm::vec4(-0.1, -0.2, 0.0, 1.0), glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)),
};


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint vao;
GLuint vbo;

GLuint position_id;
GLuint color_id;

GLuint vbo_vertices;
GLuint vbo_colors;

// Transformation
GLfloat scalef = 1.0;
GLfloat xTranslation = 0.0;
GLfloat yTranslation = 0.0;
GLfloat zRotation = 0.0;


//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    switch (key)
    {
    case 27: glutExit(); break; // Esc
    case 70: glutFullScreen(); break; // f

    case '+': scalef += 0.1f; break; // +
    case '-': scalef -= 0.1f; break; // -
    }
}

void keyboardHandler(int key, int a, int b)
{
    switch (key)
    {
    case GLUT_KEY_UP: yTranslation += 0.1f; break; // up arrow
    case GLUT_KEY_DOWN: yTranslation -= 0.1f; break; // down arrow

    case GLUT_KEY_RIGHT: xTranslation += 0.1f; break; // right arrow
    case GLUT_KEY_LEFT: xTranslation -= 0.1f; break; // left arrow

    case GLUT_KEY_PAGE_UP: zRotation += 1.0f; break; // PgUp
    case GLUT_KEY_PAGE_DOWN: zRotation -= 1.0f; break; //PgDn
    }
}


//--------------------------------------------------------------------------------
// Transformation Matrix
//--------------------------------------------------------------------------------
void Transformation(float s, float x, float y, float z) 
{
    // Transformation Matrices
    glm::mat4 scaleTransformation = glm::mat4(1.0f);
    glm::mat4 rotateTransformation = glm::mat4(1.0f);
    glm::mat4 translateTranformation = glm::mat4(1.0f);

    scaleTransformation = glm::scale(scaleTransformation, glm::vec3(s, s, s));
    rotateTransformation = glm::rotate(rotateTransformation, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
    translateTranformation = glm::translate(translateTranformation, glm::vec3(x, y, 0.0));

    glBindBuffer(GL_ARRAY_BUFFER, vao);
    for (int i = 0; i < 16; i++)
        glBufferSubData(GL_ARRAY_BUFFER, i * (sizeof(glm::vec4) * 2),
            sizeof(glm::vec4), &(translateTranformation * rotateTransformation * scaleTransformation * star[i].position));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    // Define background
    const glm::vec4 blue = glm::vec4(0.0f, 0.0f, 0.4f, 1.0f);
    glClearBufferfv(GL_COLOR, 0, glm::value_ptr(blue));

    // Attach to program_id
    glUseProgram(program_id);

    Transformation(scalef, xTranslation, yTranslation, zRotation);

    // Render using the vao
    glBindVertexArray(vao);

    glLoadIdentity();
    glTranslatef(xTranslation, yTranslation, 0.0);
    glRotatef(zRotation, 0.0, 0.0, 1.0);

    glDrawArrays(GL_LINE_LOOP, 0, 16);
    glBindVertexArray(0);

    // Swap buffers
    glutSwapBuffers();
}

void Render(int n)
{
    Render();
    glutTimerFunc(DELTA, Render, 0);
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

void InitBuffers()
{
    // Position and color vbo
    glGenBuffers(1, &vbo);                                              // Generate buffer object names (in this case 1)
    glBindBuffer(GL_ARRAY_BUFFER, vbo);                                 // Bind named buffer object
    glBufferData(GL_ARRAY_BUFFER, sizeof(star), star, GL_STATIC_DRAW);  // Create and initialize buffer object’s data store
    glBindBuffer(GL_ARRAY_BUFFER, 0);                                   // Unbind

    // Allocate memory for the vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

    // Locations of attribute variables
    position_id = glGetAttribLocation(program_id, "position");
    color_id = glGetAttribLocation(program_id, "color");        

    // Bind buffer object
    glBindBuffer(GL_ARRAY_BUFFER, vbo); 

    // Create pointers to positions in the VAO
    glVertexAttribPointer(position_id, 4, GL_FLOAT, GL_FALSE,
        sizeof(VertexFormat), 0);

    // Create pointers to colors in the VAO
    glVertexAttribPointer(color_id, 4, GL_FLOAT, GL_FALSE,
        sizeof(VertexFormat), (void*)(sizeof(glm::vec4)));

    // Enable attribute arrays
    glEnableVertexAttribArray(position_id);
    glEnableVertexAttribArray(color_id);

    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitBuffers();

    glutTimerFunc(DELTA, Render, 0);

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
