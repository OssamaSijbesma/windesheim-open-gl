#pragma once

enum geometry_type { plane, cube, circle, sphere, cylinder, cone, torus, null };

class geometrymanager
{
public:
	static geometrymanager* get_instance();
	GLuint vao(geometry_type type, GLuint shader_id);
	GLuint build_vao(GLuint shader_id, const char* path, int* vao_size);
	int vao_size(geometry_type type);

private:
	geometrymanager();
	static geometrymanager* instance;
	GLuint vaos[null] = { 0 };
	int vao_sizes[null] = { 0 };
};

