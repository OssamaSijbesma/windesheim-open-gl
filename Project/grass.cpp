#include "grass.h"
material* grass::_material = nullptr;
texture* grass::_texture = nullptr;

grass::grass() : object()
{
	geo_type = plane;
	shader = lambert;
}


material* grass::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.07, 0.23, 0.07);
		_material->diffuse_color = glm::vec3(0.13, 0.51, 0.24);
	}

	return _material;
}

texture* grass::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/grass.bmp");
		_texture->active = true;
	}

	return _texture;
}
