#include "teapot.h"

teapot::teapot()
{
	geo = new geometry();
	bool obj = loadOBJ("Objects/teapot.obj", geo->vertices, geo->uvs, geo->normals);
	
	mat = new material();
	mat->ambient_color = glm::vec3(2.0, 0.0, 0.0);
	mat->diffuse_color = glm::vec3(2.0, 2.0, 0.0);
	mat->specular = glm::vec3(1.0f);
	mat->power = 1024;

	tex = new texture();
	tex->texture_id = loadBMP("Textures/Yellobrk.bmp");
	tex->active = true;
}
