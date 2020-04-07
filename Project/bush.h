#pragma once
#include "object.h"

class bush : public object
{
public:
	bush();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};

