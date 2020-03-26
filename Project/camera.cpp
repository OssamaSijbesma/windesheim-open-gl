#include "camera.h"

camera::camera()
{

	// movement eye and center change
	// looking only center
	speed = 0.5f;
	yaw = 0;
	pitch = 0;

	position = new glm::vec3(0.0, 0.0, 0.0);
	direction = new glm::vec3(0.0, 0.0, 0.0);

	view = new glm::mat4(glm::lookAt(
		glm::vec3(10.0, 2.0, 0.0),  // eye
		glm::vec3(0.0, 3.0, 0.0),	// center
		glm::vec3(0.0, 1.0, 0.0)	// up
	));
}

camera::~camera()
{
	delete view;
}

glm::mat4 camera::get_view()
{
	*position = glm::vec3(x_pos, 2.0f, z_pos);

	*direction = glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
		sin(glm::radians(pitch)), 
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);

	*view = glm::mat4(glm::lookAt(
		*position,					//eye
		*direction,					//center
		glm::vec3(0.0, 1.0, 0.0)	// up
	));

	return  *view;
}

void camera::process_input(unsigned char key, int a, int b)
{
	switch (key)
	{

	case'w':
		z_pos += speed;
		break;
	case'a':
		x_pos += speed;
		break;
	case's':
		z_pos -= speed;
		break;
	case'd':
		x_pos -= speed;
		break;

	case'i':
		pitch += 10.0f;
		break;
	case'j':
		yaw += 10.0f;
		break;
	case'k':
		pitch -= 10.0f;
		break;
	case'l':
		yaw -= 10.0f;
		break;
	}
}
