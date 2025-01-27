

#ifndef __SPHERE__
#define __SPHERE__
#include "GeometricObject.h"

class Sphere : public GeometricObject
{
public:
	Sphere();
	Sphere(glm::vec3 center, float radius, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	~Sphere();
	bool hit(const Ray& ray, double& t, ShadeInfo& shadeInfo);
	glm::vec3 center;
	float radius;
	void print();
	glm::dvec3 calcNormal(glm::dvec3 point);
	bool equals(const Sphere &s2);
	int sphereID;
};
#endif