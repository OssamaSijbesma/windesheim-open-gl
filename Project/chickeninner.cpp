#include "chickeninner.h"
GLuint* chickeninner::vao = nullptr;
int* chickeninner::vao_size = nullptr;
material* chickeninner::_material = nullptr;
texture* chickeninner::_texture = nullptr;

chickeninner::chickeninner()
{
	geo_type = cube;
}

const GLuint& chickeninner::get_vao(GLuint shader_id) const
{
	geometrymanager* g = geometrymanager::get_instance();
	return g->vao(geo_type, shader_id);
}

const int& chickeninner::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* chickeninner::get_material()
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

texture* chickeninner::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = true;
	}

	return _texture;
}
