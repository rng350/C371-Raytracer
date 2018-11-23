#include "GeometricObject.h"
#ifndef __TRIANGLE__
#define __TRIANGLE__
class Triangle : public GeometricObject
{
public:
	Triangle();
	Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	~Triangle();

	bool hit(const Ray& ray, double& t, ShadeInfo& shadeInfo);

	glm::vec3 v1, v2, v3, flat_normal;
	void print();
};
#endif