#include "MeshTriangle.h"

MeshTriangle::MeshTriangle(){}

MeshTriangle::MeshTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
	glm::vec3 n1, glm::vec3 n2, glm::vec3 n3,
	glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess)
	: Triangle(v1, v2, v3, amb_col, diff_col, spe_col, shininess)
{
	this->n1 = n1;
	this->n2 = n2;
	this->n3 = n3;
}

MeshTriangle::~MeshTriangle(){}

// computes the normal at a given point in the triangle, interpolating from the normals at the 3 points
// an assumption is made that the coordinates you enter actually are in the triangle
glm::vec3 MeshTriangle::computeNormalAt(float x, float y, float z)
{
	// use barycentric coordinates
	// calculate distances of given point from triangle points
	glm::vec3 given_point = glm::vec3(x, y, z);
	float length1 = abs(glm::distance(given_point, this->v1));
	float length2 = abs(glm::distance(given_point, this->v2));
	float length3 = abs(glm::distance(given_point, this->v3));

	// closeness... ratio? Dunno what to even call this
	// Basically, the closer your point is to this triangle corner in
	// comparison to the other two points, the higher its value will be
	// value will range from 0 to 1 (inclusive)
	float lengths_sum = length1 + length2 + length3;
	float length_1_percentage = 1.0 - length1 / lengths_sum;
	float length_2_percentage = 1.0 - length2 / lengths_sum;
	float length_3_percentage = 1.0 - length3 / lengths_sum;

	return this->n1 * length_1_percentage
		+ this->n2 * length_2_percentage
		+ this->n3 * length_3_percentage;
}

void MeshTriangle::print()
{
	//(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
	//glm::vec3 n1, glm::vec3 n2, glm::vec3 n3,
	//	glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	std::cout << "MESH-TRI: v1: <" << v1.x << "," << v1.y << "," << v1.z << ">" <<
		"\n- v2: <" << v2.x << "," << v2.y << "," << v2.z << ">" <<
		"\n- v3: <" << v3.x << "," << v3.y << "," << v3.z << ">" <<
		"\n- n1: <" << n1.x << "," << n1.y << "," << n1.z << ">" <<
		"\n- n2: <" << n2.x << "," << n2.y << "," << n2.z << ">" <<
		"\n- n3: <" << n3.x << "," << n3.y << "," << n3.z << ">" <<
		"\n- flat_n: <" << flat_normal.x << "," << flat_normal.y << "," << flat_normal.z << ">" <<
		"\n- a: <" << amb_col.x << "," << amb_col.y << "," << amb_col.z << ">"
		"\n- d: <" << diff_col.x << "," << diff_col.y << "," << diff_col.z << ">" <<
		"\n- s: <" << spe_col.x << "," << spe_col.y << "," << spe_col.z << ">" <<
		"\n- shin: " << shininess << std::endl;
}
