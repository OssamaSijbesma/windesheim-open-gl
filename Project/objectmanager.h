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

#include "teapot.h"
#include "camera.h"
#include "plane.h"
#include <list>
#include "objectmanager.h"

class objectmanager
{
public:
	objectmanager();
	~objectmanager();
	std::list<object*> get_objects();
	void build_objects(GLuint program_id);
private:
	void create_objects();
	std::list<object*> objects;
};

