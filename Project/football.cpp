#include "football.h"
material* football::_material = nullptr;
texture* football::_texture = nullptr;

football::football()
{
	geo_type = sphere;
	spin = 0;
}

const GLuint& football::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& football::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* football::get_material()
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

texture* football::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/football.bmp");
		_texture->active = true;
	}

	return _texture;
}

void football::animate()
{
	if (direction)
	{
		_rotation.x += 1.5;
		_rotation.y += 1.5;
		_position.z += 0.06;
	}
	else
	{
		_rotation.x -= 1.5;
		_rotation.y -= 1.5;
		_position.z -= 0.06;
	}

	update_model();

	if (_position.z > 40 || _position.z < 30)
		direction = !direction;
}
