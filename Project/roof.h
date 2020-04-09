#pragma once
#include "object.h"

class roof : public object
{
public:
	roof();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};
