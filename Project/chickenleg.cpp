#include "chickenleg.h"
vao* chickenleg::_vao = nullptr;
material* chickenleg::_material = nullptr;
texture* chickenleg::_texture = nullptr;

chickenleg::chickenleg()
{
	shader = lambert;
}

const vao& chickenleg::get_vao(GLuint shader_id) const
{
	if (_vao == nullptr)
	{
		_vao = new vao();
		*_vao = geometrymanager::get_instance()->load_vao(shader_id, "Objects/chickenlegs.obj");
	}

	return *_vao;
}

material* chickenleg::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.122, 0.05, 0.0);
		_material->diffuse_color = glm::vec3(0.200, 0.100, 0.0);
	}

	return _material;
}

texture* chickenleg::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = true;
	}

	return _texture;
}
