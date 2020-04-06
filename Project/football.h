#pragma once
#include "object.h"
class football : public object
{
public:
	football();
	const virtual GLuint& get_vao(GLuint shader_id) const;
	const virtual int& get_vao_size() const;
	virtual material* get_material();
	virtual texture* get_texture();
	virtual void animate();

private:
	static material* _material;
	static texture* _texture;
	int spin;
	bool direction;
};

