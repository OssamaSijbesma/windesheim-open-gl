#include "pavement.h"

material* pavement::mat = nullptr;
texture* pavement::tex = nullptr;

pavement::pavement()
{
	geo_type = plane;
}

const GLuint& pavement::get_vao(GLuint shader_id) const
{
	geometrymanager* g = geometrymanager::get_instance();
	return g->vao(geo_type, shader_id);
}

const int& pavement::get_vao_size() const
{
	return geometrymanager::get_instance()->vao_size(geo_type);
}

material* pavement::get_material()
{
	if (mat == nullptr)
	{
		mat = new material();
		mat->ambient_color = glm::vec3(0.255, 0.255, 0.169);
		mat->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
		mat->specular = glm::vec3(16.0f);
		mat->power = 1024;
	}

	return mat;
}

texture* pavement::get_texture()
{
	if (tex == nullptr)
	{
		tex = new texture();
		tex->texture_id = loadBMP("Textures/pavement.bmp");
		tex->active = true;
	}

	return tex;
}
