#pragma once
#include <GL/glew.h>
#include <GL/freeglut.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "glsl.h"
#include "objloader.h"
#include "texture.h"
#include "object.h"

#include "camera.h"
#include "plane.h"
#include <list>
#include "objectmanager.h"

class objectmanager
{
public:
	objectmanager();
	~objectmanager();
	std::vector<object*> get_objects();
	void build_objects(GLuint program_id);
private:
	void init_world();
	std::vector<object*>* create_house();
	std::vector<object*>* create_playground();
	std::vector<object*>* create_floor();
	std::vector<object*> objects;
	const int floor[36][12] = {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0},
		{0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0},
		{0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0},
		{0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0},
		{0, 0, 1, 1, 2, 2, 2, 2, 2, 2, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
	};
};

