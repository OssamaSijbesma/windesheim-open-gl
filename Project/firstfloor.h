#pragma once
#include "object.h"

class firstfloor : public object
{
public:
	firstfloor();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};
