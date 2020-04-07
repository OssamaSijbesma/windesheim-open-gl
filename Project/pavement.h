#pragma once
#include "object.h"

class pavement : public object
{
public:
	pavement();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};

