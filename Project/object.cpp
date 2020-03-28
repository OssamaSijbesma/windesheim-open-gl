#include "object.h"

object::object()
{
	geo = nullptr;
	mat = nullptr;
	tex = nullptr;
	model = new glm::mat4();
}

object::~object()
{
	if (geo != nullptr)
		delete geo;
	if (mat != nullptr)
		delete mat;	
	if (tex != nullptr)
		delete tex;
	delete model;
}

geometry* object::get_geometry()
{
	return geo;
}

material* object::get_material()
{
	return mat;
}

texture* object::get_texture()
{
	return tex;
}

glm::mat4 object::get_model()
{
	return *model;
}

void object::position(float x, float y, float z)
{
	*model = glm::translate(*model, glm::vec3(x, y, z));
}

void object::rotate_x(float angle)
{
	*model = glm::rotate(*model, glm::radians(angle), glm::vec3(1.0, 0.0, 0.0));
}

void object::rotate_y(float angle)
{
	*model = glm::rotate(*model, glm::radians(angle), glm::vec3(0.0, 1.0, 0.0));
}

void object::rotate_z(float angle)
{
	*model = glm::rotate(*model, glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
}

void object::scale(float size)
{
	*model = glm::scale(*model, glm::vec3(size, size, size));
}

