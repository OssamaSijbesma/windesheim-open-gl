#include "bush.h"
material* bush::_material = nullptr;
texture* bush::_texture = nullptr;

bush::bush()
{
	geo_type = cube;
	shader = lambert;
}

material* bush::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.07, 0.23, 0.07);
		_material->diffuse_color = glm::vec3(0.13, 0.51, 0.24);
	}

	return _material;
}

texture* bush::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/grass.bmp");
		_texture->active = true;
	}

	return _texture;
}
