#include "glm/glm.hpp"
#include "Ray.h"
#include "ShadeInfo.h"
#include <cmath>
#include <iostream>
#include "enums.h"

#ifndef GEO_OBJ
#define GEO_OBJ

class GeometricObject
{
public:
	GeometricObject();
	GeometricObject(glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	~GeometricObject();
	virtual bool hit(const Ray& ray, double& t, ShadeInfo& shadeInfo) = 0;
	glm::vec3 amb_col, diff_col, spe_col;
	float shininess;
};
#endif