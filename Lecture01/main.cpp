#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glsl.h"

using namespace std;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

//--------------------------------------------------------------------------------
// Vars
//--------------------------------------------------------------------------------

GLuint program_id;
GLuint position_id;
GLuint color_id;

glm::vec4 position;
glm::vec4 color;


//--------------------------------------------------------------------------------
// Keyboard handling
//--------------------------------------------------------------------------------

void keyboardHandler(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();
}

//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------


void Render()
{
    //initShaders();



    static const GLfloat blue[] = { 0.0, 0.0, 0.4, 1.0 };
    glClearBufferfv(GL_COLOR, 0, blue);

    glPointSize(40.0f);
    glDrawArrays(GL_POINTS, 0, 1);


    /*
    //Quads
    glBegin(GL_QUADS);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.5, -0.5);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0.5, 0.5);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-0.5, 0.5);
    glEnd();


    glBegin(GL_TRIANGLES);
    glColor3f(1.0, 1.0, 0.0);
    glVertex2f(-0.5, -0.5);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(0.5, -0.5);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(0, 0.5);
    glEnd();
    */



    glutSwapBuffers();
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// void InitShaders()
// Initializes Glut, Glew and Shaders
//------------------------------------------------------------

void InitGlutGlew(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);

    glewInit();
}

void InitShaders()
{
    char* vertexshader = glsl::readFile("vertexshader.vsh");
    GLuint vsh_id = glsl::makeVertexShader(vertexshader);

    char* fragshader = glsl::readFile("fragmentshader.fsh");
    GLuint fsh_id = glsl::makeFragmentShader(fragshader);

    program_id = glsl::makeShaderProgram(vsh_id, fsh_id);
    glUseProgram(program_id);

    // Create vector
    position = glm::vec4(0.3f, -0.4f, 0.0f, 1.0f);
    color = glm::vec4(1.0, 1.0, 0.0, 0.0);

    // Get location of uniform variable (create if new)
    position_id = glGetUniformLocation(program_id, "position");
    color_id = glGetUniformLocation(program_id, "color");

    // Specify the value of the uniform variable
    // Args: location, count, value
    glUniform4fv(position_id, 1, glm::value_ptr(position));
    glUniform4fv(color_id, 1, glm::value_ptr(color));
}



int main(int argc, char ** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();

    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    glutMainLoop();

    return 0;
}