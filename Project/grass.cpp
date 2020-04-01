#include "grass.h"
geometry* grass::grass_geometry = nullptr;
material* grass::grass_material = nullptr;
texture* grass::grass_texture = nullptr;

grass::grass() : object()
{


}

geometry* grass::get_geometry()
{
	if (grass_geometry == nullptr)
	{
		grass_geometry = new geometry();
		bool obj = loadOBJ("Objects/plane.obj", grass_geometry->vertices, grass_geometry->uvs, grass_geometry->normals);
	}

	return grass_geometry;
}

material* grass::get_material()
{
	if (grass_material == nullptr)
	{
		grass_material = new material();
		grass_material->ambient_color = glm::vec3(0.15, 0.232, 0.12);
		grass_material->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
		grass_material->specular = glm::vec3(0.0f);
		grass_material->power = 1024;
	}

	return grass_material;
}

texture* grass::get_texture()
{
	if (grass_texture == nullptr)
	{
		grass_texture = new texture();
		grass_texture->texture_id = loadBMP("Textures/grass.bmp");
		grass_texture->active = true;
	}

	return grass_texture;
}
