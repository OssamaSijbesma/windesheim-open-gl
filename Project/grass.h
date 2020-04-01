#pragma once
#include "object.h"

class grass : public object
{
public:
	grass();
	virtual geometry* get_geometry();
	virtual material* get_material();
	virtual texture* get_texture();
private:
	static geometry* grass_geometry;
	static material* grass_material;
	static texture* grass_texture;
};

