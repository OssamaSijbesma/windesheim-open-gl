#pragma once
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "texture.h"
#include "geometrymanager.h"

using namespace std;

enum shader_type { phong, lambert };

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
	const virtual GLuint& get_vao(GLuint shader_id) const;
	const virtual int& get_vao_size() const;
	virtual material* get_material() = 0;
	virtual texture* get_texture() = 0;
	virtual void animate();
	glm::mat4 get_model();
	shader_type get_shader_type();
	void position(float x, float y, float z);
	void rotate_x(float angle);
	void rotate_y(float angle);
	void rotate_z(float angle);
	void scale(float size);
	void scale_x(float size);
	void scale_y(float size);
	void scale_z(float size);

protected:
	geometry_type geo_type;
	shader_type shader;
	void update_model();
	static material* mat;
	static texture* tex;
	glm::mat4* model;
	glm::vec3 _position;
	glm::vec3 _rotation;
	glm::vec3 _scale;
};
