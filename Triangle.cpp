#include "Triangle.h"

Triangle::Triangle()
{

}

Triangle::Triangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess) : GeometricObject(amb_col, diff_col, spe_col, shininess)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
	this->flat_normal = glm::normalize(glm::cross(v2 - v1, v3 - v1));
}
bool Triangle::hit(const Ray& ray, double& t, ShadeInfo& shadeInfo)
{
	double offset = 0.000001;

	//step 1: check if it's in the same plane as the triangle
	float temp_t;
	glm::vec3 ray_orig = ray.getOrigin();
	glm::vec3 ray_dir = ray.getDirection();
	float d = -(flat_normal.x*v1.x) - (flat_normal.y*v1.y) - (flat_normal.z*v1.z);

	float n_dot_d = glm::dot(flat_normal, ray_dir);

	if (abs(n_dot_d) < offset)
		return false;
	temp_t = -(glm::dot(flat_normal, ray_orig) + d)
		/ (n_dot_d);
	if (temp_t <= 0.0)
		return false;

	glm::vec3 vc = ray_orig + (temp_t * ray_dir);

	//step 2: check if it's in the triangle itself
	glm::vec3 triangle_area_total = (glm::cross(v2 - v1, v3 - v1) / 2.0f);
	float alpha = glm::length((glm::cross(vc - v2, vc - v3) / 2.0f) / triangle_area_total);
	float beta = glm::length((glm::cross(vc - v2, vc - v1) / 2.0f) / triangle_area_total);
	float epsilon = glm::length((glm::cross(vc - v3, vc - v1) / 2.0f) / triangle_area_total);

	if (abs(1 - (alpha + beta + epsilon)) > offset)
		return false;
}

void Triangle::print()
{
	//(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	//flat_normal
	std::cout << "TRIANGLE:\n- v1: <" << v1.x << "," << v1.y << "," << v1.z << ">" <<
		"\n- v2: <" << v2.x << "," << v2.y << "," << v2.z << ">" <<
		"\n- v3: <" << v3.x << "," << v3.y << "," << v3.z << ">" <<
		"\n- flat_n: <" << flat_normal.x << "," << flat_normal.y << "," << flat_normal.z << ">" <<
		"\n- a: <" << amb_col.x << "," << amb_col.y << "," << amb_col.z << ">"
		"\n- d: <" << diff_col.x << "," << diff_col.y << "," << diff_col.z << ">" <<
		"\n- s: <" << spe_col.x << "," << spe_col.y << "," << spe_col.z << ">" <<
		"\n- shin: " << shininess << std::endl;
}


Triangle::~Triangle()
{

}