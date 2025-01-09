#include "BoundingBox.h"

BoundingBox::BoundingBox() {}
BoundingBox::BoundingBox(glm::vec3 max, glm::vec3 min)
{
	this->max = max;
	this->min = min;
}
BoundingBox::~BoundingBox() {};

// AABB
bool BoundingBox::hit(const Ray& ray)
{
	glm::dvec3 ray_orig = ray.getOrigin();
	glm::dvec3 ray_dir = ray.getDirection();

	glm::dvec3 t_max;
	glm::dvec3 t_min;

	double a = 1.0 / ray_dir.x;
	if (a >= 0.0)
	{
		t_min.x = (min.x - ray_orig.x) * a;
		t_max.x = (max.x - ray_orig.x) * a;
	}
	else
	{
		t_min.x = (max.x - ray_orig.x) * a;
		t_max.x = (min.x - ray_orig.x) * a;
	}

	double b = 1.0 / ray_dir.y;
	if (b >= 0.0)
	{
		t_min.y = (min.y - ray_orig.y) * b;
		t_max.y = (max.y - ray_orig.y) * b;
	}
	else
	{
		t_min.y = (max.y - ray_orig.y) * b;
		t_max.y = (min.y - ray_orig.y) * b;
	}

	double c = 1.0 / ray_dir.z;
	if (c >= 0.0)
	{
		t_min.z = (min.z - ray_orig.z) * c;
		t_max.z = (max.z - ray_orig.z) * c;
	}
	else
	{
		t_min.z = (max.z - ray_orig.z) * c;
		t_max.z = (min.z - ray_orig.z) * c;
	}

	double t0, t1;

	// find largest enterting t value
	if (t_min.x > t_min.y) {
		t0 = t_min.x;
	}
	else
	{
		t0 = t_min.y;
	}

	if (t_min.z > t0)
	{
		t0 = t_min.z;
	}

	// find smallest exiting t value
	if (t_max.x < t_max.y)
	{
		t1 = t_max.x;
	}
	else
	{
		t1 = t_max.y;
	}
	if (t_max.z < t1)
	{
		t1 = t_max.z;
	}

	if (t0 < t1 && t1 > 0.0)
		return true;
	else return false;
}