#pragma once
#include "object.h"
class football : public object
{
public:
	football();
	virtual material* get_material();
	virtual texture* get_texture();
	virtual void animate();

private:
	static material* _material;
	static texture* _texture;
	bool direction;
};

