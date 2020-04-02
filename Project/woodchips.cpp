#include "woodchips.h"

material* woodchips::mat = nullptr;
texture* woodchips::tex = nullptr;

woodchips::woodchips()
{
	geo_type = plane;
}

const GLuint& woodchips::get_vao(GLuint shader_id) const
{
	return geometrymanager::get_instance()->vao(geo_type, shader_id);
}

const int& woodchips::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* woodchips::get_material()
{
	if (mat == nullptr)
	{
		mat = new material();
		mat->ambient_color = glm::vec3(0.255, 0.202, 0.12);
		mat->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
		mat->specular = glm::vec3(0.0f);
		mat->power = 2;
	}

	return mat;
}

texture* woodchips::get_texture()
{
	if (tex == nullptr)
	{
		tex = new texture();
		tex->texture_id = loadBMP("Textures/woodchips.bmp");
		tex->active = true;
	}

	return tex;
}
