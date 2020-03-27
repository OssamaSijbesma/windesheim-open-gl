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

#include "teapot.h"
#include "camera.h"
#include "plane.h"
#include <list>

using namespace std;

//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;
unsigned const int DELTA_TIME = 10;
const int ARRAY_SIZE = 3;

const char* fragshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

camera cam;

//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint texture_id;

// Uniform ID's
GLuint uniform_mv;
GLuint uniform_proj;
GLuint uniform_light_pos;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_specular;
GLuint uniform_material_power;

std::list<object*> objects;
object* obj;

// Matrices
glm::mat4 projection = glm::perspective(
    glm::radians(45.0f),
    1.0f * WIDTH / HEIGHT, 0.1f,
    20.0f);
glm::mat4 mv;


//--------------------------------------------------------------------------------
// Keyboard Wrapper
//--------------------------------------------------------------------------------

void KeyboardProxy(unsigned char key, int a, int b)
{
    if (key == 27)
        glutExit();

    cam.process_input(key, a, b);
}


//--------------------------------------------------------------------------------
// Rendering
//--------------------------------------------------------------------------------

void Render()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_MULTISAMPLE);

    // Attach to program_id
    glUseProgram(program_id);

    for (object* obj : objects)
    {

        // Set camera model and view matrix
        mv = obj->get_model() * cam.get_view();

        material* material = obj->get_material();
        texture* texture = obj->get_texture();

        // Fill uniform vars
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));
        glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(uniform_light_pos, 1, glm::value_ptr(material->light_position));
        glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(material->ambient_color));
        glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(material->diffuse_color));
        glUniform3fv(uniform_specular, 1, glm::value_ptr(material->specular));
        glUniform1f(uniform_material_power, material->power);

        // Send mvp
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv));

        // load the right texture
        glBindTexture(GL_TEXTURE_2D, texture->texture_id);

        // Send vao
        glBindVertexArray(obj->vao);
        glDrawArrays(GL_TRIANGLES, 0, obj->get_geometry()->vertices.size());
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
    glutSetOption(GLUT_MULTISAMPLE, 16);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
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
    // Attribute id's
    GLuint position_id = glGetAttribLocation(program_id, "position");
    GLuint normal_id = glGetAttribLocation(program_id, "normal");
    GLuint uv_id = glGetAttribLocation(program_id, "uv");

    // vbo's
    GLuint vbo_vertices;
    GLuint vbo_normals;
    GLuint vbo_uvs;

    for (object* obj : objects)
    {

        geometry* g = obj->get_geometry();

        // vbo for vertices
        glGenBuffers(1, &vbo_vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER,
            g->vertices.size() * sizeof(glm::vec3),
            &g->vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // vbo for normals
        glGenBuffers(1, &vbo_normals);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glBufferData(GL_ARRAY_BUFFER,
            g->normals.size() * sizeof(glm::vec3),
            &g->normals[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // vbo for uvs
        glGenBuffers(1, &vbo_uvs);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
        glBufferData(GL_ARRAY_BUFFER,
            g->uvs.size() * sizeof(glm::vec2),
            &g->uvs[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Allocate memory for vao
        glGenVertexArrays(1, &obj->vao);

        // Bind to vao
        glBindVertexArray(obj->vao);

        // Bind vertices to vao
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glVertexAttribPointer(position_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(position_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Bind normals to vao
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glVertexAttribPointer(normal_id, 3, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(normal_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Bind uvs to vao
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
        glVertexAttribPointer(uv_id, 2, GL_FLOAT, GL_FALSE, 0, 0);
        glEnableVertexAttribArray(uv_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Stop bind to vao
        glBindVertexArray(0);

    }

    // Make uniform vars
    uniform_mv = glGetUniformLocation(program_id, "mv");
    uniform_proj = glGetUniformLocation(program_id, "projection");
    uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
    uniform_material_ambient = glGetUniformLocation(program_id, "mat_ambient");
    uniform_material_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
    uniform_specular = glGetUniformLocation(program_id, "mat_specular");
    uniform_material_power = glGetUniformLocation(program_id, "mat_power");

    // Send mvp
    glUseProgram(program_id);
}

void InitObjects() 
{
    plane* tp = new plane();
     objects.push_back(tp);
}

int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitObjects();
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
