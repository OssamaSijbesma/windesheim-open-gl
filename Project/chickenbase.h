#pragma once
#include "object.h"

class chickenbase : public object
{
public:
	chickenbase();
	virtual material* get_material();
	virtual texture* get_texture();
private:
	static material* _material;
	static texture* _texture;
};
