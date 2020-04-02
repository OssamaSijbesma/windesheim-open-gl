#include "chickenleg.h"
GLuint* chickenleg::vao = nullptr;
int* chickenleg::vao_size = nullptr;
material* chickenleg::_material = nullptr;
texture* chickenleg::_texture = nullptr;

chickenleg::chickenleg()
{
	vao_size = new int();
}

const GLuint& chickenleg::get_vao(GLuint shader_id) const
{
	if (vao == nullptr) 
	{
		vao = new GLuint();
		*vao = geometrymanager::get_instance()->build_vao(shader_id, "Objects/chickenlegs.obj", vao_size);
	}
	
	return *vao;
}

const int& chickenleg::get_vao_size() const
{
	return *vao_size;
}

material* chickenleg::get_material()
{
	if (_material == nullptr)
	{
		_material = new material();
		_material->ambient_color = glm::vec3(0.122, 0.05, 0.0);
		_material->diffuse_color = glm::vec3(1.0, 1.0, 0.0);
		_material->specular = glm::vec3(0.0f);
		_material->power = 1024;
	}

	return _material;
}

texture* chickenleg::get_texture()
{
	if (_texture == nullptr)
	{
		_texture = new texture();
		_texture->texture_id = loadBMP("Textures/wood.bmp");
		_texture->active = true;
	}

	return _texture;
}
