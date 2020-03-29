#include "grass.h"

grass::grass()
{
	geo = new geometry();
	bool obj = loadOBJ("Objects/plane.obj", geo->vertices, geo->uvs, geo->normals);

	mat = new material();
	mat->ambient_color = glm::vec3(0.0, 0.0, 0.0);
	mat->diffuse_color = glm::vec3(2.0, 2.0, 2.0);
	mat->specular = glm::vec3(0.0f);
	mat->power = 1024;

	tex = new texture();
	tex->texture_id = loadBMP("Textures/grass.bmp");
	tex->active = true;
}
