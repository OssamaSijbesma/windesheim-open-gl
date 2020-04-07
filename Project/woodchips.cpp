#include "woodchips.h"

material* woodchips::_material = nullptr;
texture* woodchips::_texture = nullptr;

woodchips::woodchips()
{
	geo_type = plane;
	shader = lambert;
}

material* woodchips::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.188, 0.137, 0.0);
		_material->diffuse_color = glm::vec3(0.419, 0.337, 0.0);
	}

	return _material;
}

texture* woodchips::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/woodchips.bmp");
		_texture->active = true;
	}

	return _texture;
}
