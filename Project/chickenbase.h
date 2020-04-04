#pragma once
#include "object.h"

class chickenbase : public object
{
public:
	chickenbase();
	const virtual GLuint& get_vao(GLuint shader_id) const;
	const virtual int& get_vao_size() const;
	virtual material* get_material();
	virtual texture* get_texture();
private:
	static material* _material;
	static texture* _texture;
};
