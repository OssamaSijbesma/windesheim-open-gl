#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera
{
public:
	camera();
	~camera();
	glm::mat4 getViewModel();
	void processInput(unsigned char key, int a, int b);
private:
	float speed;
	glm::mat4* view;
	glm::mat4* model;
};

