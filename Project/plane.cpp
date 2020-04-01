#include "plane.h"
geometry* plane::geo = nullptr;
material* plane::mat = nullptr;
texture* plane::tex = nullptr;

plane::plane()
{

}

geometry* plane::get_geometry()
{
	if (geo == nullptr)
	{
		geo = new geometry();
		bool obj = loadOBJ("Objects/plane.obj", geo->vertices, geo->uvs, geo->normals);
	}

	return geo;
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
