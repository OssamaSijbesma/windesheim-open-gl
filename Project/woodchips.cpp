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
		_material->ambient_color = glm::vec3(0.288, 0.237, 0.0);
		_material->diffuse_color = glm::vec3(0.519, 0.437, 0.0);
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
