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
	// Singleton variable with lazy initialization

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
	// Singleton variable with lazy initialization

	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/planks_vertical.bmp");
		_texture->active = true;
	}

	return _texture;
}
