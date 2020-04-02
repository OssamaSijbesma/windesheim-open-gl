#include <iostream>
#include <vector>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "object.h"

#include "camera.h"
#include "plane.h"
#include <list>
#include "objectmanager.h"

using namespace std;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 1280, HEIGHT = 720;
unsigned const int DELTA_TIME = 10;

const char* fragshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// Program ID
GLuint program_id;

// Uniform ID's
GLuint uniform_mv;
GLuint uniform_projection;
GLuint uniform_ambient;
GLuint uniform_diffuse;
GLuint uniform_specular;
GLuint uniform_power;

camera _camera;
objectmanager _objectmanager;

// Projection Matrix
glm::mat4 projection = glm::perspective(
    glm::radians(45.0f),
    1.0f * WIDTH / HEIGHT, 0.1f,
    120.0f); // View distance

// View Matrix * Model Matrix
glm::mat4 viewmodel;


//--------------------------------------------------------------------------------
// Keyboard Wrapper
//--------------------------------------------------------------------------------

void KeyboardProxy(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();

    _camera.process_input(key, a, b);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);

    // Attach to program_id
    glUseProgram(program_id);

    for (object* obj : _objectmanager.get_objects())
    {

        // Set camera model and view matrix
        viewmodel = _camera.get_view() * obj->get_model();

        material* material = obj->get_material();
        texture* texture = obj->get_texture();

        // Fill uniform vars
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(viewmodel));
        glUniform3fv(uniform_ambient, 1, glm::value_ptr(material->ambient_color));
        glUniform3fv(uniform_diffuse, 1, glm::value_ptr(material->diffuse_color));
        glUniform3fv(uniform_specular, 1, glm::value_ptr(material->specular));
        glUniform1f(uniform_power, material->power);

        // Send mvp
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(viewmodel));

        // load the right texture
        glBindTexture(GL_TEXTURE_2D, texture->texture_id);

        // Send vao
        glBindVertexArray(obj->get_vao(program_id));
        glDrawArrays(GL_TRIANGLES, 0, obj->get_vao_size());
        glBindVertexArray(0);
    }

    glutSwapBuffers();
}


//------------------------------------------------------------
// void Render(int n)
// Render method that is called by the timer function
//------------------------------------------------------------

void Render(int n)
{
    // Render
    Render();

    glutTimerFunc(DELTA_TIME, Render, 0);
}


//------------------------------------------------------------
// void InitGlutGlew(int argc, char **argv)
// Initializes Glut and Glew
//------------------------------------------------------------

void InitGlutGlew(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutSetOption(GLUT_MULTISAMPLE, 8);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Project OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(KeyboardProxy);
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
// void InitBuffers()
// Allocates and fills buffers
//------------------------------------------------------------

void InitBuffers()
{
    _objectmanager.init_world();

    // Make uniform vars
    uniform_mv = glGetUniformLocation(program_id, "mv");
    uniform_ambient = glGetUniformLocation(program_id, "mat_ambient");
    uniform_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
    uniform_specular = glGetUniformLocation(program_id, "mat_specular");
    uniform_power = glGetUniformLocation(program_id, "mat_power");

    // Send mvp
    glUseProgram(program_id);

    // Projection matrix 
    glUniformMatrix4fv(glGetUniformLocation(program_id, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

    // Directional light simulating the sun.
    glUniform3fv(glGetUniformLocation(program_id, "light_pos"), 1, glm::value_ptr(glm::vec3(4, 4, 4)));
}


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitBuffers();
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    // Hide console window
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);

    // Main loop
    glutMainLoop();

    return 0;
}
