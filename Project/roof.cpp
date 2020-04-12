#include "roof.h"
material* roof::_material = nullptr;
texture* roof::_texture = nullptr;

roof::roof()
{
	geo_type = plane;
	shader = lambert;
}

material* roof::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.374, 0.260, 0.158);
		_material->diffuse_color = glm::vec3(0.474, 0.298, 0.149);
	}

	return _material;
}

texture* roof::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/roof.bmp");
		_texture->active = true;
	}

	return _texture;
}
