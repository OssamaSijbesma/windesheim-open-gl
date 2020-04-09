#pragma once
#include "object.h"

class canopy : public object
{
public:
	canopy();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};


