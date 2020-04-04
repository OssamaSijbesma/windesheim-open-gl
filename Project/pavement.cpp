#include "pavement.h"

material* pavement::_material = nullptr;
texture* pavement::_texture = nullptr;

pavement::pavement()
{
	geo_type = plane;
}

const GLuint& pavement::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& pavement::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* pavement::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.255, 0.255, 0.169);
		_material->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
		_material->specular = glm::vec3(16.0f);
		_material->power = 1024;
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
