#include "object.h"

object::object()
{
	geo = nullptr;
	mat = nullptr;
	tex = nullptr;
}

object::~object()
{
	if (geo != nullptr)
		delete geo;
	if (mat != nullptr)
		delete mat;	
	if (tex != nullptr)
		delete tex;
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