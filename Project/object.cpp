#include "object.h"

object::object()
{
	geo_type = null;
	shader = phong;
	model = new glm::mat4();
	_position = glm::vec3(0, 0, 0);
	_rotation = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1.0, 1.0, 1.0);
}

object::~object()
{
	delete model;
}

const vao& object::get_vao(GLuint shader_id) const
{
	// Returns vao
	return geometrymanager::get_instance()->get_vao(shader_id, geo_type);
}

void object::animate()
{
	// Animation behaviour
}

glm::mat4 object::get_model()
{
	// Returns model
	return *model;
}

shader_type object::get_shader_type()
{
	// Returns shader
	return shader;
}

void object::position(float x, float y, float z)
{
	// Sets xyz positions
	_position = glm::vec3(x, y, z);
	update_model();
}

void object::rotate_x(float angle)
{
	// Set rotation on the x-axis
	_rotation.x = angle;
	update_model();
}

void object::rotate_y(float angle)
{
	// Set rotation on the y-axis
	_rotation.y = angle;
	update_model();
}

void object::rotate_z(float angle)
{
	// Set rotation on the z-axis
	_rotation.z = angle;
	update_model();
}

void object::scale(float size)
{
	// Set the scale for the xyz
	_scale = glm::vec3(size, size, size);
	update_model();
}

void object::scale_x(float size)
{
	// Set the scale for the x-axis
	_scale.x = size;
	update_model();
}

void object::scale_y(float size)
{
	// Set the scale for the y-axis
	_scale.y = size;
	update_model();
}

void object::scale_z(float size)
{
	// Set the sclae on the z-axis
	_scale.z = size;
	update_model();
}

void object::update_model()
{
	// Update the model in the right 
	*model = glm::translate(glm::mat4(), _position);
	*model = glm::rotate(*model, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
	*model = glm::rotate(*model, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
	*model = glm::rotate(*model, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
	*model = glm::scale(*model, _scale);
}


