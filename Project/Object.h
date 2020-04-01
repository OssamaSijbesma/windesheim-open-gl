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
	glm::vec3 ambient_color;	// Ambient lighting, simulates light from other sources.
	glm::vec3 diffuse_color;	// Diffuse lighting, simulates the directional impact a light object has on an object.
	glm::vec3 specular;			// Specular lightning, simulates the bright spot of a light.
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
	virtual ~object();
	virtual geometry* get_geometry() = 0;
	virtual material* get_material() = 0;
	virtual texture* get_texture() = 0;
	glm::mat4 get_model();
	void position(float x, float y, float z);
	void rotate_x(float angle);
	void rotate_y(float angle);
	void rotate_z(float angle);
	void scale(float size);
	GLuint vao;

protected:
	static texture* tex;
	static geometry* geo;
	static material* mat;
	glm::mat4* model;
};
