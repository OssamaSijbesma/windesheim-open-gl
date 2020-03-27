#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera
{
public:
	camera();
	~camera();
	glm::mat4 get_view();
	void process_input(unsigned char key, int a, int b);
private:
	const float WALK_SPEED = 0.5f;
	const float TURN_SPEED = 1.0f;
	float pitch;
	float yaw;
	glm::vec3* position;
	glm::vec3* direction;
	glm::mat4* view;
};

