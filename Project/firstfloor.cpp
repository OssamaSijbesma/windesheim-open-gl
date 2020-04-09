#include "firstfloor.h"
material* firstfloor::_material = nullptr;
texture* firstfloor::_texture = nullptr;

firstfloor::firstfloor()
{
	geo_type = cube;
	shader = lambert;
}

material* firstfloor::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.355, 0.355, 0.269);
		_material->diffuse_color = glm::vec3(0.400, 0.400, 0.300);
	}

	return _material;
}

texture* firstfloor::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/pavement.bmp");
		_texture->active = true;
	}

	return _texture;
}
