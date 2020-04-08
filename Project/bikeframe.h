#pragma once
#include "object.h"

class bikeframe : public object
{
public:
	bikeframe();
	const virtual vao& get_vao(GLuint shader_id) const;
	virtual material* get_material();
	virtual texture* get_texture();
	virtual void animate();

private:
	static vao* _vao;
	static material* _material;
	static texture* _texture;
};

