#include "objectmanager.h"
#include "grass.h"



objectmanager::objectmanager()
{

}

objectmanager::~objectmanager()
{
}

std::list<object*> objectmanager::get_objects()
{
    return objects;
}

void objectmanager::build_objects(GLuint program_id)
{
    create_objects();

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
}


void objectmanager::create_objects()
{
    grass* tp = new grass();
    tp->position(0, 0, 0);
    grass* pl = new grass();
    pl->position(2, 0, 0);
    objects.push_back(tp);
    objects.push_back(pl);
}
