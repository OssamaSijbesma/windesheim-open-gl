#include "chickenbase.h"
material* chickenbase::_material = nullptr;
texture* chickenbase::_texture = nullptr;

chickenbase::chickenbase()
{
	geo_type = cube;
}

const GLuint& chickenbase::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& chickenbase::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* chickenbase::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.122, 0.05, 0.0);
		_material->diffuse_color = glm::vec3(-1.0, 1.0, 1.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 512;
	}

	return _material;
}

texture* chickenbase::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = true;
	}

	return _texture;
}
