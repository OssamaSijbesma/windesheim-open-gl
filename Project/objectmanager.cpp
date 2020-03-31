#include "objectmanager.h"
#include "pavement.h"
#include "grass.h"
#include "woodchips.h"



objectmanager::objectmanager()
{
}

objectmanager::~objectmanager()
{
}

std::vector<object*> objectmanager::get_objects()
{
    return objects;
}

void objectmanager::build_objects(GLuint program_id)
{
    init_world();

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


void objectmanager::init_world()
{
    std::vector<object*>* floor = create_floor();
    objects.insert(objects.end(), floor->begin(), floor->end());

}

vector<object*>* objectmanager::create_house()
{
    vector<object*>* house = new vector<object*>();

    return house;
}

vector<object*>* objectmanager::create_playground()
{
    vector<object*>* playground = new vector<object*>();

    return playground;
}

std::vector<object*>* objectmanager::create_floor()
{
    vector<object*>* floor_tiles = new vector<object*>();

    for (int z = 0; z < sizeof(floor) / sizeof(floor[0]); z++)
        for (int x = 0; x < sizeof(floor[0]) / sizeof(int); x++)
        {
            object* tile;

            switch (floor[z][x])
            {
            case 0: tile = new pavement(); break;
            case 1: tile = new grass(); break;
            case 2: tile = new woodchips(); break;
            default: tile = new plane(); break;
            }

            tile->position(x*2, 0, z*2);
            floor_tiles->push_back(tile);
        }

    return floor_tiles;
}



