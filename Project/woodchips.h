#pragma once
#include "object.h"

class woodchips : public object
{
public:
	woodchips();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};

