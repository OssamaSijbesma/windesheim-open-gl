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
	float speed;
	float pitch;
	float yaw;
	float x_pos;
	float z_pos;
	glm::vec3* position;
	glm::vec3* direction;
	glm::mat4* view;
};

