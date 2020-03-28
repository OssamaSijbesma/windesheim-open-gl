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
public:
	object();
	~object();
	geometry* get_geometry();
	material* get_material();
	texture* get_texture();
	glm::mat4 get_model();
	void position(float x, float y, float z);
	void rotate_x(float angle);
	void rotate_y(float angle);
	void rotate_z(float angle);
	void scale(float size);
	GLuint vao;

protected:
	texture* tex;
	geometry* geo;
	material* mat;
	glm::mat4* model;
};
