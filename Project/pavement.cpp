#include "pavement.h"
geometry* pavement::geo = nullptr;
material* pavement::mat = nullptr;
texture* pavement::tex = nullptr;

pavement::pavement()
{

}

geometry* pavement::get_geometry()
{
	if (geo == nullptr)
	{
		geo = new geometry();
		bool obj = loadOBJ("Objects/plane.obj", geo->vertices, geo->uvs, geo->normals);
	}

	return geo;
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
