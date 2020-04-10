#include "pole.h"
material* pole::_material = nullptr;
texture* pole::_texture = nullptr;

pole::pole()
{
	geo_type = cylinder;
	shader = lambert;
}

material* pole::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.7, 0.621, 0.429);
		_material->diffuse_color = glm::vec3(0.696, 0.676, 0.480);
	}

	return _material;
}

texture* pole::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->active = false;
	}

	return _texture;
}
