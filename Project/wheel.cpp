#include "wheel.h"
vao* wheel::_vao = nullptr;
material* wheel::_material = nullptr;
texture* wheel::_texture = nullptr;

wheel::wheel()
{
	shader = lambert;
}

const vao& wheel::get_vao(GLuint shader_id) const
{
	if (_vao == nullptr)
	{
		_vao = new vao();
		*_vao = geometrymanager::get_instance()->load_vao(shader_id, "Objects/wheel.obj");
	}

	return *_vao;
}

material* wheel::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.184, 0.309, 0.501);
		_material->diffuse_color = glm::vec3(0.278, 0.466, 0.749);
	}

	return _material;
}

texture* wheel::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->active = false;
	}

	return _texture;
}

void wheel::animate()
{

	
	if (_position.z < -50)
		_position.z = 50;

	_position.z -= 0.05;
	_rotation.z -= 1;
	update_model();
}
