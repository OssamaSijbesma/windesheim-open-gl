#pragma once

enum geometry_type { plane, cube, circle, sphere, cylinder, cone, torus, null };

class geometrymanager
{
public:
	static geometrymanager* get_instance();
	GLuint vao(geometry_type type, GLuint shader_id);
	int vao_size(geometry_type type);

private:
	geometrymanager();
	GLuint build_vao(geometry_type type, GLuint shader_id, const char* path);
	static geometrymanager* instance;
	GLuint vaos[null] = { 0 };
	int vao_sizes[null] = { 0 };
};

