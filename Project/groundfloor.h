#pragma once
#include "object.h"

class groundfloor : public object
{
public:
	groundfloor();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};

