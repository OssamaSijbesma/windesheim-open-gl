#include "wheel.h"
GLuint* wheel::vao = nullptr;
int* wheel::vao_size = nullptr;
material* wheel::_material = nullptr;
texture* wheel::_texture = nullptr;

wheel::wheel()
{
	vao_size = new int();
	spin = 0.0;
}

const GLuint& wheel::get_vao(GLuint shader_id) const
{
	if (vao == nullptr)
	{
		vao = new GLuint();
		*vao = geometrymanager::get_instance()->build_vao(shader_id, "Objects/wheel.obj", vao_size);
	}

	return *vao;
}

const int& wheel::get_vao_size() const
{
	return *vao_size;
}

material* wheel::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.0, 0.0, 0.0);
		_material->diffuse_color = glm::vec3(1.0, 1.0, 1.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 1024;
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
	if (_position.z < 0)
		_position.z = 70;

	_position.z -= 0.05;
	_rotation.z -= 1;
	update_model();
}
