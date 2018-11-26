#include "Sphere.h"
#include <iostream>
#include <algorithm>

Sphere::Sphere()
{
	this->amb_col = glm::vec3(0, 0, 0);
	this->diff_col = glm::vec3(0, 0, 0);
	this->spe_col = glm::vec3(0, 0, 0);
	this->shininess = -1;
	this->center = glm::vec3(0,0,0);
	this->radius = -1;
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
	glm::dvec3 ray_orig = ray.getOrigin();
	glm::dvec3 ray_dir = ray.getDirection();

	/*
	std::cout << "ray orig <" << ray_orig.x << ",";
	std::cout << ray_orig.y << ",";
	std::cout << ray_orig.z << ">";
	std::cout << "ray dir <" << ray_dir.x << ",";
	std::cout << ray_dir.y << ",";
	std::cout << ray_dir.z << ">" << std::endl;
	*/
	double a = glm::dot(ray_dir, ray_dir);
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

	// if the lower value is negative, use the higher one instead
	if (temp_t < 0.00001)
		temp_t = std::max(((-b + sqrt(b*b - 4.0*a*c)) / (2 * a)), ((-b - sqrt(b*b - 4 * a*c)) / (2 * a)));
	
	// and if that one is negative too...
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
			shadeInfo.hit_coord = ray.pointAtParameter(temp_t);
			shadeInfo.surface_norm = calcNormal(ray_orig + ray_dir*t);
			shadeInfo.hit_obj = Sphere_Hit;
		}
	}
	return true;
}
glm::dvec3 Sphere::calcNormal(glm::dvec3 point)
{
	return glm::normalize(glm::dvec3((point.x - center.x)/radius, (point.y - center.y)/radius, (point.z-center.z)/radius));
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

bool Sphere::equals(const Sphere& s2)
{

	return
		(this->center.x == s2.center.x)
		&& (this->center.y == s2.center.y)
		&& (this->center.z == s2.center.z)
		&& (this->radius == s2.radius)
		&& (this->amb_col.x == s2.amb_col.x)
		&& (this->amb_col.y == s2.amb_col.y)
		&& (this->amb_col.z == s2.amb_col.z)
		&& (this->diff_col.x == s2.diff_col.x)
		&& (this->diff_col.y == s2.diff_col.y)
		&& (this->diff_col.z == s2.diff_col.z)
		&& (this->spe_col.x == s2.spe_col.x)
		&& (this->spe_col.y == s2.spe_col.y)
		&& (this->spe_col.z == s2.spe_col.z)
		&& (this->shininess == s2.shininess)
		;
}