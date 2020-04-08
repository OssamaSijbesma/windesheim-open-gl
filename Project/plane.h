#pragma once
#include "object.h"

class plane : public object
{
public:
	plane();
	const virtual vao& get_vao(GLuint shader_id) const;
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* mat;
	static texture* tex;
};

