#include "box.h"

box::box()
{
	geo = new geometry();
	bool obj = loadOBJ("Objects/box.obj", geo->vertices, geo->uvs, geo->normals);

	mat = new material();
	mat->light_position = glm::vec3(4, 4, 4);
	mat->ambient_color = glm::vec3(2.0, 0.0, 0.0);
	mat->diffuse_color = glm::vec3(2.0, 2.0, 0.0);
	mat->specular = glm::vec3(1.0f);
	mat->power = 1024;

	tex = new texture();
	tex->texture_id = loadBMP("Textures/Yellobrk.bmp");
	tex->active = true;
}
