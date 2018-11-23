#ifndef __MESH__
#define __MESH__

#include "GeometricObject.h"
#include "MeshTriangle.h"
#include <iostream>
#include "objloader.h"

class Mesh : public GeometricObject
{
public:
	Mesh();
	Mesh(std::string filename, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess);
	~Mesh();
	bool hit(const Ray& ray, double& t, ShadeInfo& shadeInfo);
	std::vector<Triangle> triangles;
	std::string filename;
	void loadMeshes();
	void print();
};
#endif