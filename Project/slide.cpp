#include "slide.h"
GLuint* slide::vao = nullptr;
int* slide::vao_size = nullptr;
material* slide::_material = nullptr;
texture* slide::_texture = nullptr;

slide::slide()
{
	vao_size = new int();
}

const GLuint& slide::get_vao(GLuint shader_id) const
{
	if (vao == nullptr)
	{
		vao = new GLuint();
		*vao = geometrymanager::get_instance()->build_vao(shader_id, "Objects/slide.obj", vao_size);
	}

	return *vao;
}

const int& slide::get_vao_size() const
{
	return *vao_size;
}

material* slide::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.113, 0.254, 0.0);
		_material->diffuse_color = glm::vec3(1.0, 1.0, 1.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 512;
	}

	return _material;
}

texture* slide::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = false;
	}

	return _texture;
}
