#include "woodchips.h"

material* woodchips::_material = nullptr;
texture* woodchips::_texture = nullptr;

woodchips::woodchips()
{
	geo_type = plane;
}

const GLuint& woodchips::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& woodchips::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* woodchips::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.255, 0.202, 0.12);
		_material->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 2;
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
