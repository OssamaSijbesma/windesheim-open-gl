#include "woodchips.h"
geometry* woodchips::geo = nullptr;
material* woodchips::mat = nullptr;
texture* woodchips::tex = nullptr;

woodchips::woodchips()
{

}

geometry* woodchips::get_geometry()
{
	if (geo == nullptr)
	{
		geo = new geometry();
		bool obj = loadOBJ("Objects/plane.obj", geo->vertices, geo->uvs, geo->normals);
	}

	return geo;
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
