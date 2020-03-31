#include "camera.h"
#include <iostream>

camera::camera()
{
	view_mode = false;
	yaw = 0.0f;
	pitch = 0.0f;
	position = new glm::vec3(0.0f, 2.0f, 0.0f);
	direction = new glm::vec3(0.0f, 0.0f, 0.0f);
	view = new glm::mat4();
}

camera::~camera()
{
	delete position;
	delete direction;
	delete view;
}

glm::mat4 camera::get_view()
{
	// Set the direction with the yaw and pitch coordinates.
	*direction = glm::vec3(
		cos(glm::radians(yaw)) * cos(glm::radians(pitch)), 
		sin(glm::radians(pitch)), 
		sin(glm::radians(yaw)) * cos(glm::radians(pitch))
	);

	// Set the view with the position and direction.
	*view = glm::mat4(glm::lookAt(
		*position,									//eye, the position of the camera.
		*position + glm::normalize(*direction),		//center, the direction the camera is pointed at.
		glm::vec3(0.0, 1.0, 0.0)					// up, no need to change.
	));

	return  *view;
}

void camera::process_input(unsigned char key, int a, int b)
{
	// For movement we change the eye and center position.
	// For the direction we are looking at we only need to change the center.
	switch (key)
	{
	case'c':
		view_mode = !view_mode;
		*position = (view_mode) ?
			glm::vec3(0.0f, 30.0f, 0.0f) :
			glm::vec3(0.0f, 2.0f, 0.0f);
		*direction = (view_mode) ?
			glm::vec3(0.0f, 0.0f, 0.0f) :
			glm::vec3(0.0f, 0.0f, 0.0f);
		break;

	case'w': // Forward
		*position += (view_mode) ? 
			glm::vec3(direction->x, direction->y, direction->z) * WALK_SPEED :
			glm::vec3(direction->x, 0.0f, direction->z) * WALK_SPEED;
		break;
	case's': // Backward
		*position -= (view_mode) ?
			glm::vec3(direction->x, direction->y, direction->z) * WALK_SPEED :
			glm::vec3(direction->x, 0.0f, direction->z) * WALK_SPEED;
		break;
	case'a': // Left
		*position += (view_mode) ? 
			glm::cross(glm::vec3(0.0, 1.0, 0.0), glm::vec3(direction->x, direction->y, direction->z)) * WALK_SPEED :
			glm::cross(glm::vec3(0.0, 1.0, 0.0), glm::vec3(direction->x, 0.0f, direction->z)) * WALK_SPEED;
		break;
	case'd': // Right
		*position += (view_mode) ? 
			glm::cross(glm::vec3(direction->x, direction->y, direction->z), glm::vec3(0.0, 1.0, 0.0)) * WALK_SPEED :
			glm::cross(glm::vec3(direction->x, 0.0f, direction->z), glm::vec3(0.0, 1.0, 0.0)) * WALK_SPEED;
		break;

	case'i': // Look up
		pitch += TURN_SPEED;
		break;
	case'k': // Look down
		pitch -= TURN_SPEED;
		break;
	case'q':
	case'j': // Look left
		yaw -= TURN_SPEED;
		break;
	case'e':
	case'l': // Look right
		yaw += TURN_SPEED;
		break;
	}
}
