#include "chickenbody.h"
GLuint* chickenbody::vao = nullptr;
int* chickenbody::vao_size = nullptr;
material* chickenbody::_material = nullptr;
texture* chickenbody::_texture = nullptr;

chickenbody::chickenbody()
{
	vao_size = new int();
}

const GLuint& chickenbody::get_vao(GLuint shader_id) const
{
	if (vao == nullptr)
	{
		vao = new GLuint();
		*vao = geometrymanager::get_instance()->build_vao(shader_id, "Objects/chickenbody.obj", vao_size);
	}

	return *vao;
}

const int& chickenbody::get_vao_size() const
{
	return *vao_size;
}

material* chickenbody::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.113, 0.254, 0.0);
		_material->diffuse_color = glm::vec3(0.150, 0.300, 0.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 512;
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
