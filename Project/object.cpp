#include "object.h"

object::object()
{
	geo = nullptr;
	mat = nullptr;
	tex = nullptr;
	model = new glm::mat4();
}

object::~object()
{
	if (geo != nullptr)
		delete geo;
	if (mat != nullptr)
		delete mat;	
	if (tex != nullptr)
		delete tex;
	delete model;
}

geometry* object::get_geometry()
{
	return geo;
}

material* object::get_material()
{
	return mat;
}

texture* object::get_texture()
{
	return tex;
}

glm::mat4 object::get_model()
{
	return *model;
}
