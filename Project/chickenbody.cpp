#include "chickenbody.h"
vao* chickenbody::_vao = nullptr;
material* chickenbody::_material = nullptr;
texture* chickenbody::_texture = nullptr;

chickenbody::chickenbody()
{
	shader = lambert;
}

const vao& chickenbody::get_vao(GLuint shader_id) const
{
	if (_vao == nullptr)
	{
		_vao = new vao();
		*_vao = geometrymanager::get_instance()->load_vao(shader_id, "Objects/chickenbody.obj");
	}

	return *_vao;
}

material* chickenbody::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.113, 0.254, 0.0);
		_material->diffuse_color = glm::vec3(0.150, 0.300, 0.0);
	}

	return _material;
}

texture* chickenbody::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = false;
	}

	return _texture;
}
