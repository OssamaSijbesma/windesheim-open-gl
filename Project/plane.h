#pragma once
#include "object.h"

class plane : public object
{
public:
	plane();
	const virtual GLuint& get_vao(GLuint shader_id) const;
	const virtual int& get_vao_size() const;
	virtual material* get_material();
	virtual texture* get_texture();

private:
	static material* mat;
	static texture* tex;
};

