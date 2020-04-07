#include "grass.h"
material* grass::_material = nullptr;
texture* grass::_texture = nullptr;

grass::grass() : object()
{
	geo_type = plane;
}


material* grass::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.15, 0.232, 0.12);
		_material->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 1024;
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
