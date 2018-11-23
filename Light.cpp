#include "Light.h"



Light::Light()
{
}

Light::Light(glm::vec3 pos, glm::vec3 col)
{
	this->pos = pos;
	this->col = col;
}

Light::~Light()
{
}

void Light::print()
{
	std::cout << "LIGHT:\n- pos: <" << pos.x << "," << pos.y << "," << pos.z << ">" <<
		"\n- col: <" << col.x << "," << col.y << "," << col.z << ">" << std::endl;
}
