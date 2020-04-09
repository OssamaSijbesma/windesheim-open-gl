#pragma once
#include "object.h"

using namespace std;

class skybox : public object
{
public:
	skybox();
	virtual material* get_material();
	virtual texture* get_texture();
private:
	static material* _material;
	static texture* _texture;
	bool direction;
};