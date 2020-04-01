#pragma once
#include "object.h"

class pavement : public object
{
public:
	pavement();
	virtual geometry* get_geometry();
	virtual material* get_material();
	virtual texture* get_texture();
private:
	static geometry* geo;
	static material* mat;
	static texture* tex;
};

