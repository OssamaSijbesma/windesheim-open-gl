#include "slide.h"
vao* slide::_vao = nullptr;
material* slide::_material = nullptr;
texture* slide::_texture = nullptr;

slide::slide()
{
}

const vao& slide::get_vao(GLuint shader_id) const
{
	// Singleton variable with lazy initialization

	if (_vao == nullptr)
	{
		_vao = new vao();
		*_vao = geometrymanager::get_instance()->load_vao(shader_id, "Objects/slide.obj");
	}

	return *_vao;
}

material* slide::get_material()
{
	// Singleton variable with lazy initialization

	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.440, 0.440, 0.440);
		_material->diffuse_color = glm::vec3(0.650, 0.650, 0.650);
		_material->specular = glm::vec3(1.0f);
		_material->power = 256;
	}

	return _material;
}

texture* slide::get_texture()
{
	// Singleton variable with lazy initialization

	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = false;
	}

	return _texture;
}
