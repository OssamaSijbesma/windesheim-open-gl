#include "plane.h"

material* plane::mat = nullptr;
texture* plane::tex = nullptr;

plane::plane()
{

}

const GLuint& plane::get_vao(GLuint shader_id) const
{
	return 0;
}

const int& plane::get_vao_size() const
{
	return 0;
}

material* plane::get_material()
{
	if (mat == nullptr)
	{
		mat = new material();
		mat->ambient_color = glm::vec3(2.0, 0.0, 0.0);
		mat->diffuse_color = glm::vec3(2.0, 2.0, 0.0);
		mat->specular = glm::vec3(1.0f);
		mat->power = 1024;
	}

	return mat;
}

texture* plane::get_texture()
{
	if (tex == nullptr)
	{
		tex = new texture();
		tex->texture_id = loadBMP("Textures/Yellobrk.bmp");
		tex->active = true;
	}

	return tex;
}
