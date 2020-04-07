#pragma once
#include "object.h"

class grass : public object
{
public:
	grass();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};

