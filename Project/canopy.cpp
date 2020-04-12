#include "canopy.h"
material* canopy::_material = nullptr;
texture* canopy::_texture = nullptr;

canopy::canopy()
{
	geo_type = cube;
	shader = lambert;
}

material* canopy::get_material()
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

texture* canopy::get_texture()
{
	// Singleton variable with lazy initialization

	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/planks_horizontal.bmp");
		_texture->active = true;
	}

	return _texture;
}
