#pragma once
#include "object.h"

class woodchips : public object
{
public:
	woodchips();
	virtual geometry* get_geometry();
	virtual material* get_material();
	virtual texture* get_texture();
private:
	static geometry* geo;
	static material* mat;
	static texture* tex;
};

