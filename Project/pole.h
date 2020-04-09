#pragma once
#include "object.h"

class pole : public object
{
public:
	pole();
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* _material;
	static texture* _texture;
};