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

	/*
	std::cout << "ray orig <" << ray_orig.x << ",";
	std::cout << ray_orig.y << ",";
	std::cout << ray_orig.z << ">";
	std::cout << "ray dir <" << ray_dir.x << ",";
	std::cout << ray_dir.y << ",";
	std::cout << ray_dir.z << ">" << std::endl;
	*/
	double a = 1.0;
	double b = 2.0*
			(ray_dir.x*(ray_orig.x - center.x)
			+ ray_dir.y*(ray_orig.y - center.y)
			+ ray_dir.z*(ray_orig.z - center.z));
	double c = (ray_orig.x  - center.x)*(ray_orig.x  - center.x)
				+ (ray_orig.y  - center.y)*(ray_orig.y  - center.y)
				+ (ray_orig.z  - center.z)*(ray_orig.z  - center.z)
				- (radius*radius);

	if ((b*b - 4*a*c) < 0.0)
		return false;

	double temp_t = std::min(((-b + sqrt(b*b - 4.0*a*c))/(2*a)), ((-b - sqrt(b*b - 4*a*c))/(2*a)));

	if (temp_t < 0.00001)
		return false;
	else
	{
		if (temp_t < t)
		{
			t = temp_t;
			shadeInfo.amb_col = this->amb_col;
			shadeInfo.diff_col = this->diff_col;
			shadeInfo.spe_col = this->spe_col;
			shadeInfo.shininess = this->shininess;
			shadeInfo.hit_an_obj = true;
			shadeInfo.surface_norm = calcNormal(ray_orig + ray_dir*(float)t);
		}
	}
	return true;
}
glm::vec3 Sphere::calcNormal(glm::vec3 point)
{
	return glm::vec3((point.x - center.x)/radius, (point.y - center.y)/radius, (point.z-center.z)/radius);
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
