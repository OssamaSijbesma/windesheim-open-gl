#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object
{
	struct Properties {
		glm::vec3 light_position;
		glm::vec3 ambient_color;
		glm::vec3 diffuse_color;
		glm::vec3 specular;
		float power;
	};
public:
	Object();
	~Object();
private:
	vector<glm::vec3> normals;
	vector<glm::vec3> vertices;
	vector<glm::vec2> uvs;
	Properties prop;
};
 

