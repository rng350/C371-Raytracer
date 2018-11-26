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
	std::cout << "TRIANGLE FLAT NORMAL: " << flat_normal.x << "," << flat_normal.y << "," << flat_normal.z << std::endl;
}
bool Triangle::hit(const Ray& ray, double& t, ShadeInfo& shadeInfo)
{
	//step 1: check if it's in the same plane as the triangle
	double temp_t;
	glm::vec3 ray_orig = ray.getOrigin();
	glm::vec3 ray_dir = ray.getDirection();
	float n_dot_d = glm::dot(flat_normal, ray_dir);

	float d = glm::dot(flat_normal, -v1);

	if ((n_dot_d) == 0)
		return false;
	// temp_t = (glm::dot(flat_normal, (v1 - ray_orig))) / (n_dot_d);
	// test
	temp_t = -(glm::dot(flat_normal, ray_orig) + d) / (n_dot_d);

	// if negative, then the point is behind ray origin
	if ((temp_t) < 0.00001)
		return false;

	glm::vec3 vc = ray_orig + ((float)temp_t * ray_dir);

	//step 2: check if it's in the triangle itself
	float triangle_area_total = glm::length(glm::cross(v2 - v1, v3 - v1));
	float alpha = glm::length(glm::cross(vc - v2, vc - v3)) / triangle_area_total;
	float beta = glm::length(glm::cross(vc - v2, vc - v1)) / triangle_area_total;
	float epsilon = glm::length(glm::cross(vc - v3, vc - v1)) / triangle_area_total;

	if ((alpha + beta + epsilon) > 1.0f)
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
			shadeInfo.surface_norm = this->flat_normal;
		}
		return true;
	}
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