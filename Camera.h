#include "glm/glm.hpp"
#include <iostream>

#ifndef CAMERAH
#define CAMERAH

class Camera
{
public:
	Camera();
	Camera(glm::vec3 pos, float fov, float focal_length, float aspect_ratio);
	~Camera();
	glm::vec3 pos;
	float fov, focal_length, aspect_ratio;
	void print();
};

#endif