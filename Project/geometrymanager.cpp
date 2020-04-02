#include <GL/glew.h>

#include <glm/glm.hpp>

#include <vector>

#include "objloader.h"
#include "geometrymanager.h"

using namespace std;

geometrymanager* geometrymanager::instance = nullptr;

geometrymanager::geometrymanager() 
{
}

geometrymanager* geometrymanager::get_instance()
{
    if (instance == nullptr)
        instance = new geometrymanager();
    return instance;
}

GLuint geometrymanager::vao(geometry_type type, GLuint shader_id)
{
    if (vaos[type] == 0) 
    {
        int* size = new int();

        switch (type)
        {
        case null:
            break;
        case plane:
            vaos[type] = build_vao(shader_id, "Objects/plane.obj", size);
            break;
        case cube:
            vaos[type] = build_vao(shader_id, "Objects/cube.obj", size);
            break;
        case circle:
            vaos[type] = build_vao(shader_id, "Objects/circle.obj", size);
            break;
        case sphere:
            vaos[type] = build_vao(shader_id, "Objects/sphere.obj", size);
            break;
        case cylinder:
            vaos[type] = build_vao(shader_id, "Objects/cylinder.obj", size);
            break;
        case cone:
            vaos[type] = build_vao(shader_id, "Objects/cone.obj", size);
            break;
        case torus:
            vaos[type] = build_vao(shader_id, "Objects/torus.obj", size);
            break;
        }

        vao_sizes[type] = *size;
    }
	return vaos[type];
}

int geometrymanager::vao_size(geometry_type type)
{
    return vao_sizes[type];
}

GLuint geometrymanager::build_vao(GLuint shader_id, const char* path, int* vao_size)
{
    // geometry
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;

    // load geometry from object
    bool obj = loadOBJ(path, vertices, uvs, normals);

    *vao_size = vertices.size();
    
    // Attribute id's
    GLuint position_id = glGetAttribLocation(shader_id, "position");
    GLuint normal_id = glGetAttribLocation(shader_id, "normal");
    GLuint uv_id = glGetAttribLocation(shader_id, "uv");

    // vbo's
    GLuint vbo_vertices;
    GLuint vbo_normals;
    GLuint vbo_uvs;

    GLuint vao;

    // vbo for vertices
    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER,
        vertices.size() * sizeof(glm::vec3),
        &vertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for normals
    glGenBuffers(1, &vbo_normals);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_normals);
    glBufferData(GL_ARRAY_BUFFER,
        normals.size() * sizeof(glm::vec3),
        &normals[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // vbo for uvs
    glGenBuffers(1, &vbo_uvs);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_uvs);
    glBufferData(GL_ARRAY_BUFFER,
        uvs.size() * sizeof(glm::vec2),
        &uvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Allocate memory for vao
    glGenVertexArrays(1, &vao);

    // Bind to vao
    glBindVertexArray(vao);

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

    return vao;
}
