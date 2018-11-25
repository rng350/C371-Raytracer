#include "Plane.h"

Plane::Plane() {}

Plane::Plane(glm::vec3 pos, glm::vec3 normal, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess)
	: GeometricObject(amb_col, diff_col, spe_col, shininess)
{
	this->pos = pos;
	this->normal = normal;
}

Plane::~Plane(){}

bool Plane::hit(const Ray& ray, double& t, ShadeInfo& shadeInfo)
{
	double temp_t;
	glm::vec3 ray_orig = ray.getOrigin();
	glm::vec3 ray_dir = ray.getDirection();
	float n_dot_d = glm::dot(normal, ray_dir);

	if (abs(n_dot_d) < 0.000001)
		return false;
	temp_t = (glm::dot(normal, (pos-ray_orig)))
			/ (n_dot_d);

	// if negative, then the point is behind ray origin
	if (temp_t < 0.0)
		return false;
	else
	{
		// t was initialized at -1.0
		if ((t < 0.0) || (temp_t < t))
			t = temp_t;
		return true;
	}
}


//Plane(glm::vec3 pos, glm::vec3 normal, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
void Plane::print()
{
	std::cout << "PLANE:\n- pos: <" << pos.x << "," << pos.y << "," << pos.z << ">" <<
		"\n- n: <" << normal.x << "," << normal.y << "," << normal.z << ">" <<
		"\n- a: <" << amb_col.x << "," << amb_col.y << "," << amb_col.z << ">"
		"\n- d: <" << diff_col.x << "," << diff_col.y << "," << diff_col.z << ">" <<
		"\n- s: <" << spe_col.x << "," << spe_col.y << "," << spe_col.z << ">" <<
		"\n- shin: " << shininess << std::endl;
}