#include "Light.h"



Light::Light()
{
}

Light::Light(glm::vec3 pos, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col)
{
	this->pos = pos;
	this->amb_col = amb_col;
	this->diff_col = diff_col;
	this->spe_col = spe_col;
}

Light::~Light()
{
}

void Light::print()
{
	std::cout << "LIGHT:\n- pos: <" << pos.x << "," << pos.y << "," << pos.z << ">" <<
		"\n- a: <" << amb_col.x << "," << amb_col.y << "," << amb_col.z << ">"
		"\n- d: <" << diff_col.x << "," << diff_col.y << "," << diff_col.z << ">" <<
		"\n- s: <" << spe_col.x << "," << spe_col.y << "," << spe_col.z << ">" << std::endl;
}
