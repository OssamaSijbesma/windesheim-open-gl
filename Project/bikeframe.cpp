#include "bikeframe.h"
vao* bikeframe::_vao = nullptr;
material* bikeframe::_material = nullptr;
texture* bikeframe::_texture = nullptr;

bikeframe::bikeframe()
{
}

const vao& bikeframe::get_vao(GLuint shader_id) const
{
	if (_vao == nullptr)
	{
		_vao = new vao();
		*_vao = geometrymanager::get_instance()->load_vao(shader_id, "Objects/bikeframe.obj");
	}

	return *_vao;
}

material* bikeframe::get_material()
{
	// Singleton variable with lazy initialization

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
	// Singleton variable with lazy initialization

	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->active = false;
	}

	return _texture;
}

void bikeframe::animate()
{
	// An animation where the bike moves forward

	if (_position.z < -50)
		_position.z = 50;

	_position.z -= 0.05;
	update_model();
}
