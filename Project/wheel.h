#pragma once
#include "object.h"

class wheel : public object
{
public:
	wheel();
	const virtual GLuint& get_vao(GLuint shader_id) const;
	const virtual int& get_vao_size() const;
	virtual material* get_material();
	virtual texture* get_texture();
	virtual void animate();

private:
	static GLuint* vao;
	static int* vao_size;
	static material* _material;
	static texture* _texture;
	float spin;
};
