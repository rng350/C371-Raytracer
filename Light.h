#pragma once
#include "glm/glm.hpp"
#include <iostream>
class Light
{
public:
	Light();
	Light(glm::vec3 pos, glm::vec3 col);
	~Light();
	glm::vec3 pos, col;
	void print();
};