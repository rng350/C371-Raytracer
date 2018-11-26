#pragma once
#include "glm/glm.hpp"
#include <iostream>

class Light
{
public:
	Light();
	Light(glm::vec3 pos, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col);
	~Light();
	glm::vec3 pos;
	glm::vec3 amb_col, diff_col, spe_col;
	void print();
};