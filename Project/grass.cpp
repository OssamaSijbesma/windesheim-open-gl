#include "grass.h"
material* grass::_material = nullptr;
texture* grass::_texture = nullptr;

grass::grass() : object()
{
	geo_type = plane;
}

const GLuint& grass::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& grass::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
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
