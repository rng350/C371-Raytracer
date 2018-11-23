#include "Sphere.h"
#include <iostream>
#include <algorithm>

Sphere::Sphere()
{

}

Sphere::Sphere(glm::vec3 center, float radius, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess)
	: GeometricObject(amb_col, diff_col, spe_col, shininess)
{
	this->center = center;
	this->radius = radius;
}

Sphere::~Sphere() {}

bool Sphere::hit(const Ray& ray, double& t, ShadeInfo& shadeInfo)
{
	glm::vec3 ray_orig = ray.getOrigin();
	glm::vec3 ray_dir = ray.getDirection();

	double a = 1.0;
	double b = 2.0*(ray_dir.x*(ray_orig.x - center.x) + ray_dir.y*(ray_orig.y - center.y) + ray_dir.z*(ray_orig.z - center.z));
	double c = (ray_orig.x  - center.x)*(ray_orig.x  - center.x)
				+ (ray_orig.y  - center.y)*(ray_orig.y  - center.y)
				+ (ray_orig.z  - center.z)*(ray_orig.z  - center.z);
	if ((b*b - 4*a*c)<0)
		return false;

	double temp_t = std::min(((-b + sqrt(b*b - 4.0*a*c))/(2*a)), ((-b - sqrt(b*b - 4*a*c))/(2*a)));

	if (temp_t <= 0.0)
		return false;
	else
	{
		// t was initialized at -1.0
		if ((t < 0.0) || (temp_t < t))
			t = temp_t;
		return true;
	}
	return true;
}

void Sphere::print()
{
	//(glm::vec3 center, float radius, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	std::cout << "SPHERE:\n- center: <" << center.x << "," << center.y << "," << center.z << ">" <<
		"\n- rad: " << radius <<
		"\n- a: <" << amb_col.x << "," << amb_col.y << "," << amb_col.z << ">"
		"\n- d: <" << diff_col.x << "," << diff_col.y << "," << diff_col.z << ">" <<
		"\n- s: <" << spe_col.x << "," << spe_col.y << "," << spe_col.z << ">" <<
		"\n- shin: " << shininess << std::endl;
}
