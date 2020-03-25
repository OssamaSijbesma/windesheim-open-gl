#pragma once
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "objloader.h"
#include "texture.h"

using namespace std;

struct geometry {
	vector<glm::vec3> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> uvs;
};

struct material {
	glm::vec3 light_position;
	glm::vec3 ambient_color;
	glm::vec3 diffuse_color;
	glm::vec3 specular;
	float power;
};

struct texture {
	GLuint texture_id;
	bool active;
};


class object
{
	// mat/geo/tex

public:
	object();
	~object();
	geometry* get_geometry();
	material* get_material();
	texture* get_texture();

protected:
	texture* tex;
	geometry* geo;
	material* mat;
};
