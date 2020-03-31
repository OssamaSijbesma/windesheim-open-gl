#include "woodchips.h"

woodchips::woodchips()
{
	geo = new geometry();
	bool obj = loadOBJ("Objects/plane.obj", geo->vertices, geo->uvs, geo->normals);

	mat = new material();
	mat->ambient_color = glm::vec3(1.0, 1.0, 1.0);
	mat->diffuse_color = glm::vec3(2.0, 2.0, 2.0);
	mat->specular = glm::vec3(0.0f);
	mat->power = 2;

	tex = new texture();
	tex->texture_id = loadBMP("Textures/woodchips.bmp");
	tex->active = true;
}
