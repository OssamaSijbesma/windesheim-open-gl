#include "skybox.h"
material* skybox::_material = nullptr;
texture* skybox::_texture = nullptr;


skybox::skybox()
{
	geo_type = cube_skybox;
	shader = lambert;
}

material* skybox::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.2, 0.2, 0.2);
		_material->diffuse_color = glm::vec3(1, 1, 1);
	}

	return _material;
}

texture* skybox::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/skybox.bmp");
		_texture->active = true;
	}

	return _texture;
}
