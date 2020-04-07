#include "bikeframe.h"
GLuint* bikeframe::vao = nullptr;
int* bikeframe::vao_size = nullptr;
material* bikeframe::_material = nullptr;
texture* bikeframe::_texture = nullptr;

bikeframe::bikeframe()
{
	vao_size = new int();
}

const GLuint& bikeframe::get_vao(GLuint shader_id) const
{
	if (vao == nullptr)
	{
		vao = new GLuint();
		*vao = geometrymanager::get_instance()->build_vao(shader_id, "Objects/bikeframe.obj", vao_size);
	}

	return *vao;
}

const int& bikeframe::get_vao_size() const
{
	return *vao_size;
}

material* bikeframe::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.105, 0.105, 0.105);
		_material->diffuse_color = glm::vec3(0.196, 0.196, 0.196);
		_material->specular = glm::vec3(0.3f);
		_material->power = 1024;
	}

	return _material;
}

texture* bikeframe::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->active = false;
	}

	return _texture;
}

void bikeframe::animate()
{
	if (_position.z < 0)
		_position.z = 70;

	_position.z -= 0.05;
	update_model();
}
