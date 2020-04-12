#include "chickenbase.h"
material* chickenbase::_material = nullptr;
texture* chickenbase::_texture = nullptr;

chickenbase::chickenbase()
{
	geo_type = cube;
	shader = lambert;
}

material* chickenbase::get_material()
{
	// Singleton variable with lazy initialization

	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.122, 0.05, 0.0);
		_material->diffuse_color = glm::vec3(0.200, 0.100, 0.0);
	}

	return _material;
}

texture* chickenbase::get_texture()
{
	// Singleton variable with lazy initialization

	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = true;
	}

	return _texture;
}
