#include "football.h"
material* football::_material = nullptr;
texture* football::_texture = nullptr;

football::football()
{
	geo_type = sphere;
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

	if (_position.z > 10 || _position.z < 0)
		direction = !direction;
}
