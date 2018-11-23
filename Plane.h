#include "GeometricObject.h"

#ifndef __PLANE__
#define __PLANE__
class Plane : public GeometricObject
{
public:
	Plane();
	Plane(glm::vec3 pos, glm::vec3 normal, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	~Plane();
	bool hit(const Ray& ray, double& t, ShadeInfo& shadeInfo);
	glm::vec3 pos, normal;
	void print();
};
#endif