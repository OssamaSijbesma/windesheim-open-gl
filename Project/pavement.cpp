#include "pavement.h"

pavement::pavement()
{
	geo = new geometry();
	bool obj = loadOBJ("Objects/plane.obj", geo->vertices, geo->uvs, geo->normals);

	mat = new material();
	mat->ambient_color = glm::vec3(0.255, 0.255, 0.169);
	mat->diffuse_color = glm::vec3(0.0, 1.0, 0.0);
	mat->specular = glm::vec3(16.0f);
	mat->power = 1024;

	tex = new texture();
	tex->texture_id = loadBMP("Textures/pavement.bmp");
	tex->active = true;
}
