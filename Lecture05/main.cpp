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

using namespace std;


//--------------------------------------------------------------------------------
// Consts
//--------------------------------------------------------------------------------

const int WIDTH = 800, HEIGHT = 600;

const char* fragshader_name = "fragmentshader.fsh";
const char* vertexshader_name = "vertexshader.vsh";

unsigned const int DELTA_TIME = 10;

const int ARRAY_SIZE = 3;


//--------------------------------------------------------------------------------
// Variables
//--------------------------------------------------------------------------------

// ID's
GLuint program_id;
GLuint texture_id[ARRAY_SIZE];

// Uniform ID's
GLuint uniform_mv;
GLuint uniform_proj;
GLuint uniform_light_pos;
GLuint uniform_material_ambient;
GLuint uniform_material_diffuse;
GLuint uniform_specular;
GLuint uniform_material_power;

// Matrices
glm::mat4 view;
glm::mat4 projection;
glm::mat4 model[ARRAY_SIZE];
glm::mat4 mv[ARRAY_SIZE];

// vao
GLuint vao[ARRAY_SIZE];

// Objects
vector<glm::vec3> normals[ARRAY_SIZE];
vector<glm::vec3> vertices[ARRAY_SIZE];
vector<glm::vec2> uvs[ARRAY_SIZE];

bool obj0 = loadOBJ("Objects/teapot.obj", vertices[0], uvs[0], normals[0]);
bool obj1 = loadOBJ("Objects/box.obj", vertices[1], uvs[1], normals[1]);
bool obj2 = loadOBJ("Objects/cylinder32.obj", vertices[2], uvs[2], normals[2]);

// Attributes
glm::vec3 light_position[ARRAY_SIZE];
glm::vec3 ambient_color[ARRAY_SIZE];
glm::vec3 diffuse_color[ARRAY_SIZE];
glm::vec3 specular[ARRAY_SIZE];
float power[ARRAY_SIZE];


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
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Attach to program_id
    glUseProgram(program_id);

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        // Fill uniform vars
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv[i]));
        glUniformMatrix4fv(uniform_proj, 1, GL_FALSE, glm::value_ptr(projection));
        glUniform3fv(uniform_light_pos, 1, glm::value_ptr(light_position[i]));
        glUniform3fv(uniform_material_ambient, 1, glm::value_ptr(ambient_color[i]));
        glUniform3fv(uniform_material_diffuse, 1, glm::value_ptr(diffuse_color[i]));
        glUniform3fv(uniform_specular, 1, glm::value_ptr(specular[i]));
        glUniform1f(uniform_material_power, power[i]);

        // Do transformation
        model[i] = glm::rotate(model[i], 0.01f, glm::vec3(0.0f, 1.0f, 0.0f));
        mv[i] = view * model[i];

        // Send mvp
        glUniformMatrix4fv(uniform_mv, 1, GL_FALSE, glm::value_ptr(mv[i]));

        // load the right texture
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);


        // Send vao
        glBindVertexArray(vao[i]);
        glDrawArrays(GL_TRIANGLES, 0, vertices[0].size());
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Hello OpenGL");
    glutDisplayFunc(Render);
    glutKeyboardFunc(keyboardHandler);
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
// void InitShaders()
// Initializes the fragmentshader and vertexshader
//------------------------------------------------------------

void InitLights()
{

    light_position[0] = glm::vec3(4, 4, 4);
    ambient_color[0] = glm::vec3(2.0, 0.0, 0.0);
    diffuse_color[0] = glm::vec3(2.0, 2.0, 0.0);
    specular[0] = glm::vec3(1.0f);
    power[0] = 1024;

    light_position[1] = glm::vec3(4, 4, 4);
    ambient_color[1] = glm::vec3(1.0, 1.0, 1.0);
    diffuse_color[1] = glm::vec3(0.0, 0.0, 0.0);
    specular[1] = glm::vec3(1.0f);
    power[1] = 1024;

    light_position[2] = glm::vec3(4, 4, 4);
    ambient_color[2] = glm::vec3(0.0, 0.0, 5.0);
    diffuse_color[2] = glm::vec3(5.0, 0.0, 0.0);
    specular[2] = glm::vec3(1.0f);
    power[2] = 1024;
}

//------------------------------------------------------------
// void InitMatrices()
//------------------------------------------------------------

void InitMatrices()
{
    view = glm::lookAt(
        glm::vec3(2.0, 2.0, 7.0),  // eye
        glm::vec3(0.0, 0.0, 0.0),  // center
        glm::vec3(0.0, 1.0, 0.0));  // up

    projection = glm::perspective(
        glm::radians(45.0f),
        1.0f * WIDTH / HEIGHT, 0.1f,
        20.0f);


        model[0] = glm::mat4();
        model[1] = glm::translate(glm::mat4(), glm::vec3(3.0, 0.0, 0.0));
        model[2] = glm::translate(glm::mat4(), glm::vec3(-3.0, 0.0, 0.0));

        mv[0] = view * model[0];
        mv[1] = view * model[1];
        mv[2] = view * model[2];
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

    for (int i = 0; i < ARRAY_SIZE; i++)
    {

        // vbo for vertices
        glGenBuffers(1, &vbo_vertices);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
        glBufferData(GL_ARRAY_BUFFER,
            vertices[i].size() * sizeof(glm::vec3),
            &vertices[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // vbo for normals
        glGenBuffers(1, &vbo_normals);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
        glBufferData(GL_ARRAY_BUFFER,
            normals[i].size() * sizeof(glm::vec3),
            &normals[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // vbo for uvs
        glGenBuffers(1, &vbo_uvs);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
        glBufferData(GL_ARRAY_BUFFER,
            uvs[i].size() * sizeof(glm::vec2),
            &uvs[i][0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        // Allocate memory for vao
        glGenVertexArrays(1, &vao[i]);

        // Bind to vao
        glBindVertexArray(vao[i]);

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

        // Make uniform vars
        uniform_mv = glGetUniformLocation(program_id, "mv");
        uniform_proj = glGetUniformLocation(program_id, "projection");
        uniform_light_pos = glGetUniformLocation(program_id, "light_pos");
        uniform_material_ambient = glGetUniformLocation(program_id, "mat_ambient");
        uniform_material_diffuse = glGetUniformLocation(program_id, "mat_diffuse");
        uniform_specular = glGetUniformLocation(program_id, "mat_specular");
        uniform_material_power = glGetUniformLocation(program_id, "mat_power");

        // Define model
        mv[i] = view * model[i];

        // Send mvp
        glUseProgram(program_id);


    }
}

void InitObjects() 
{
    texture_id[0] = loadBMP("Textures/Yellobrk.bmp");
    texture_id[2] = loadBMP("Textures/Yellobrk.bmp");

}


int main(int argc, char** argv)
{
    InitGlutGlew(argc, argv);
    InitShaders();
    InitMatrices();
    InitLights();
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
