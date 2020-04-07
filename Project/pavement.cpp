#include "pavement.h"

material* pavement::_material = nullptr;
texture* pavement::_texture = nullptr;

pavement::pavement()
{
	geo_type = plane;
	shader = lambert;
}

material* pavement::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.355, 0.355, 0.269);
		_material->diffuse_color = glm::vec3(0.400, 0.400, 0.300);
	}

	return _material;
}

texture* pavement::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/pavement.bmp");
		_texture->active = true;
	}

	return _texture;
}
