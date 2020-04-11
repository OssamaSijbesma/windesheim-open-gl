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
	const float TURN_SPEED = 2.0f;
	bool view_mode;
	glm::vec3* direction;
	glm::vec3* position;
	glm::vec3* old_position;
	float pitch;
	float old_pitch;
	float yaw;
	float old_yaw;
	glm::mat4* view;
};

