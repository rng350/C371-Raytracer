// stores a bunch of relevant info for the second ray

#ifndef SHADE
#define SHADE
#include "glm/glm.hpp"

class ShadeInfo
{
public:
	ShadeInfo();
	bool hit_an_obj;
	glm::vec3 hit_coord, surface_norm;
	glm::vec3 amb_col, diff_col, spe_col;
	float shininess;
};
#endif