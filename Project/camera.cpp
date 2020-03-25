#include "camera.h"

camera::camera()
{
	speed = 0.5f;
	view = new glm::mat4(glm::lookAt(
		glm::vec3(10.0, 2.0, 0.0),  // eye
		glm::vec3(0.0, 3.0, 0.0),	// center
		glm::vec3(0.0, 1.0, 0.0)	// up
	));  

	model = new glm::mat4();
}

camera::~camera()
{
	delete view;
	delete model;
}

glm::mat4 camera::getViewModel()
{
	return *model * *view;
}

void camera::processInput(unsigned char key, int a, int b)
{
	switch (key)
	{

	case'w':
		*model = glm::translate(*model, glm::vec3(0.0, 0.0, speed));
		break;
	case'a':
		*model = glm::translate(*model, glm::vec3(speed, 0.0, 0.0));
		break;
	case's':
		*model = glm::translate(*model, glm::vec3(0.0, 0.0, -speed));
		break;
	case'd':
		*model = glm::translate(*model, glm::vec3(-speed, 0.0, 0.0));
		break;

	case'i':
		*model = glm::rotate(*model, glm::radians(-1.0f), glm::vec3(1.0, 0.0, 0.0));
		break;
	case'j':
		*model = glm::rotate(*model, glm::radians(-1.0f), glm::vec3(0.0, 1.0, 0.0));
		break;
	case'k':
		*model = glm::rotate(*model, glm::radians(1.0f), glm::vec3(1.0, 0.0, 0.0));
		break;
	case'l':
		*model = glm::rotate(*model, glm::radians(1.0f), glm::vec3(0.0, 1.0, 0.0));
		break;
	}
}
