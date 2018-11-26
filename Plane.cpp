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

	float d = glm::dot(normal, -pos);

	if ((n_dot_d) == 0.0f)
		return false;
	//temp_t = (glm::dot(normal, (pos-ray_orig))) / (n_dot_d);
	// test
	temp_t = -(glm::dot(normal, ray_orig) + d) / (n_dot_d);

	// if negative, then the point is behind ray origin
	if ((temp_t) < 0.00001)
		return false;
	else
	{
		if (temp_t < t)
		{
			t = temp_t;
			// write/rewrite info for newest hit surface
			shadeInfo.amb_col = this->amb_col;
			shadeInfo.diff_col = this->diff_col;
			shadeInfo.spe_col = this->spe_col;
			shadeInfo.shininess = this->shininess;
			shadeInfo.hit_an_obj = true;
			shadeInfo.surface_norm = this->normal;
		}
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