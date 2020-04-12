#include "geometrymanager.h"
geometrymanager* geometrymanager::instance = nullptr;

geometrymanager::geometrymanager() 
{
}

geometrymanager* geometrymanager::get_instance()
{
    // Return the singleton instance
    if (instance == nullptr)
        instance = new geometrymanager();
    return instance;
}

vao geometrymanager::get_vao(GLuint shader_id, geometry_type type)
{
    // Get the vao if it excists, otherwise create it
    if (vaos[type].id == 0)
    {
        vao temp;

        switch (type)
        {
        case null: 
            break;
        case plane: 
            temp.id = build_vao(shader_id, plane_vertices, plane_normals, plane_uvs);
            temp.size = plane_vertices.size();
            vaos[type] = temp;
            break;
        case cube:
            vaos[type] = load_vao(shader_id, "Objects/cube.obj");
            break;
        case cube_skybox:
            vaos[type] = load_vao(shader_id, "Objects/cube_inverted.obj");
            break;
        case circle:
            vaos[type] = load_vao(shader_id, "Objects/circle.obj");
            break;
        case sphere:
            vaos[type] = load_vao(shader_id, "Objects/sphere.obj");
            break;
        case cylinder:
            vaos[type] = load_vao(shader_id, "Objects/cylinder.obj");
            break;
        case cone:
            vaos[type] = load_vao(shader_id, "Objects/cone.obj");
            break;
        case torus:
            vaos[type] = load_vao(shader_id, "Objects/torus.obj");
            break;
        }
    }

    return vaos[type];
}

vao geometrymanager::load_vao(GLuint shader_id, const char* path)
{
    // geometry
    vector<glm::vec3> vertices;
    vector<glm::vec3> normals;
    vector<glm::vec2> uvs;

    loadOBJ(path, vertices, uvs, normals);
    
    vao ding;
    ding.id = build_vao(shader_id, vertices, normals, uvs);
    ding.size = vertices.size();

    return ding;
}

GLuint geometrymanager::build_vao(GLuint shader_id, vector<glm::vec3> vertices, vector<glm::vec3> normals, vector<glm::vec2> uvs)
{

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
