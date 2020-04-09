#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <vector>
#include "objloader.h"

using namespace std;

enum geometry_type { plane, cube, cube_skybox, circle, sphere, cylinder, cone, torus, null };

struct vao {
	GLuint id;
	int size;
};

class geometrymanager
{
public:
	static geometrymanager* get_instance();
	vao get_vao(GLuint shader_id, geometry_type type);
	vao load_vao(GLuint shader_id, const char* path);
	GLuint build_vao(GLuint shader_id, vector<glm::vec3> vertices, vector<glm::vec3> normals, vector<glm::vec2> uvs);

private:
	geometrymanager();
	static geometrymanager* instance;
	vao vaos[null] = {0};

    vector<glm::vec3> plane_vertices{
        glm::vec3(1.0, 0, 1.0),
        glm::vec3(-1.0, 0, -1.0),
        glm::vec3(-1.0, 0, 1.0),
        glm::vec3(1.0, 0, 1.0),
        glm::vec3(1.0, 0, -1.0),
        glm::vec3(-1.0, 0, -1.0)
    };

    vector<glm::vec3> plane_normals{
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0)
    };

    vector<glm::vec2> plane_uvs{
        glm::vec2(1.0, -0.0),
        glm::vec2(0.0, -1.0),
        glm::vec2(0.0, -0.0),
        glm::vec2(1.0, -0.0),
        glm::vec2(1.0, -1.0),
        glm::vec2(0.0, -1.0)
    };

    vector<glm::vec3> skybox_vertices{
        glm::vec3(-1.0, 1.0, -1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(-1.0, 1.0, 1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        glm::vec3(-1.0, -1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, -1.0, 1.0),
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, 1.0, 1.0),
        glm::vec3(1.0, -1.0, 1.0),
        glm::vec3(-1.0, 1.0, -1.0),
        glm::vec3(1.0, 1.0, -1.0),
        glm::vec3(1.0, -1.0, -1.0)
    };

    vector<glm::vec3> skybox_normals{
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, -1.0, 0.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(0.0, 0.0, -1.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(1.0, 0.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(0.0, 1.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(-1.0, 0.0, 0.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, 0.0, 1.0),
        glm::vec3(0.0, 0.0, 1.0)
    };

    vector<glm::vec2> skybox_uvs{
        glm::vec2(0.8750, -0.50),
        glm::vec2(0.6250, -0.750),
        glm::vec2(0.6250, -0.50),
        glm::vec2(0.6250, -0.750),
        glm::vec2(0.3750, -1.0),
        glm::vec2(0.3750, -0.750),
        glm::vec2(0.6250, -0.0),
        glm::vec2(0.3750, -0.250),
        glm::vec2(0.3750, -0.0),
        glm::vec2(0.3750, -0.50),
        glm::vec2(0.1250, -0.750),
        glm::vec2(0.1250, -0.50),
        glm::vec2(0.6250, -0.50),
        glm::vec2(0.3750, -0.750),
        glm::vec2(0.3750, -0.50),
        glm::vec2(0.6250, -0.250),
        glm::vec2(0.3750, -0.50),
        glm::vec2(0.3750, -0.250),
        glm::vec2(0.8750, -0.50),
        glm::vec2(0.8750, -0.750),
        glm::vec2(0.6250, -0.750),
        glm::vec2(0.6250, -0.750),
        glm::vec2(0.6250, -1.0),
        glm::vec2(0.3750, -1.0),
        glm::vec2(0.6250, -0.0),
        glm::vec2(0.6250, -0.250),
        glm::vec2(0.3750, -0.250),
        glm::vec2(0.3750, -0.50),
        glm::vec2(0.3750, -0.750),
        glm::vec2(0.1250, -0.750),
        glm::vec2(0.6250, -0.50),
        glm::vec2(0.6250, -0.750),
        glm::vec2(0.3750, -0.750),
        glm::vec2(0.6250, -0.250),
        glm::vec2(0.6250, -0.50),
        glm::vec2(0.3750, -0.50)
    };
};

