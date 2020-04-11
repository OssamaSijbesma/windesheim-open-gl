#include "aircraft.h"
vao* aircraft::_vao = nullptr;
material* aircraft::_material = nullptr;
texture* aircraft::_texture = nullptr;

aircraft::aircraft()
{
	
}

const vao& aircraft::get_vao(GLuint shader_id) const
{
	if (_vao == nullptr)
	{
		_vao = new vao();
		*_vao = geometrymanager::get_instance()->load_vao(shader_id, "Objects/plane.obj");
	}

	return *_vao;
}

material* aircraft::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.2, 0.2, 0.2);
		_material->diffuse_color = glm::vec3(1, 1, 1);
		_material->specular = glm::vec3(1.0f);
		_material->power = 512;
	}

	return _material;
}

texture* aircraft::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->active = false;
	}

	return _texture;
}

void aircraft::animate()
{

	*model = glm::translate(*model, glm::vec3(0.0, 0.0, 3.0));
	*model = glm::rotate(*model, glm::radians(0.8f), glm::vec3(0.0, 1.0, 0.0));

	/*
	if (_position.z < -60)
	{
		_position.z = 60;
		_position.x = 60;
	}

	_position.z -= 0.05;
	_position.x -= 0.05;
	update_model();
	*/
}
