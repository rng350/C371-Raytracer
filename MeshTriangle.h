#include "Triangle.h"

#ifndef __MESHTRIANGLE__
#define __MESHTRIANGLE__

class MeshTriangle : public Triangle
{
public:
	MeshTriangle();
	MeshTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,
		glm::vec3 n1, glm::vec3 n2, glm::vec3 n3,
		glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	~MeshTriangle();
	glm::vec3 computeNormalAt(float x, float y, float z);

	glm::vec3 n1, n2, n3;
	void print();
};
#endif