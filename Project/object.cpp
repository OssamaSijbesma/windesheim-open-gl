#include "object.h"

object::object()
{
	geo_type = null;
	model = new glm::mat4();
	_position = glm::vec3(0, 0, 0);
	_rotation = glm::vec3(0, 0, 0);
	_scale = glm::vec3(1.0, 1.0, 1.0);
}

object::~object()
{
	delete model;
}

const GLuint& object::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& object::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

void object::animate()
{
}

glm::mat4 object::get_model()
{
	return *model;
}

void object::position(float x, float y, float z)
{
	_position = glm::vec3(x, y, z);
	update_model();
}

void object::rotate_x(float angle)
{
	_rotation.x = angle;
	update_model();
}

void object::rotate_y(float angle)
{
	_rotation.y = angle;
	update_model();
}

void object::rotate_z(float angle)
{
	_rotation.z = angle;
	update_model();
}

void object::scale(float size)
{
	_scale = glm::vec3(size, size, size);
	update_model();
}

void object::scale_x(float size)
{
	_scale.x = size;
	update_model();
}

void object::scale_y(float size)
{
	_scale.y = size;
	update_model();
}

void object::scale_z(float size)
{
	_scale.z = size;
	update_model();
}

void object::update_model()
{
	*model = glm::translate(glm::mat4(), _position);
	*model = glm::rotate(*model, glm::radians(_rotation.x), glm::vec3(1.0, 0.0, 0.0));
	*model = glm::rotate(*model, glm::radians(_rotation.y), glm::vec3(0.0, 1.0, 0.0));
	*model = glm::rotate(*model, glm::radians(_rotation.z), glm::vec3(0.0, 0.0, 1.0));
	*model = glm::scale(*model, _scale);
}


