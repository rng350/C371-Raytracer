#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::string filename, glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess)
	: GeometricObject(amb_col, diff_col, spe_col, shininess)
{
	this->filename = filename;
	loadTriangles();
	genBoundingBox();
	std::cout << "MESH BOUNDING BOX: MAX<" << this->boundingBox.max.x << "," << this->boundingBox.max.y << "," << this->boundingBox.max.z << ">, MIN<" << this->boundingBox.min.x << "," << this->boundingBox.min.y << "," << this->boundingBox.min.z << ">" << std::endl;
}


bool Mesh::hit(const Ray& ray, double& t, ShadeInfo& shadeInfo)
{
	bool resp = false;
	for (int i = 0; i < triangles.size(); i++)
	{
		if (triangles[i]->hit(ray, t, shadeInfo))
			resp = true;
	}
	return resp;
}

Mesh::~Mesh()
{

}

void Mesh::loadTriangles()
{
	std::vector<glm::vec3> out_vertices, out_normals;
	std::vector<glm::vec2> out_uvs;
	filename = "../scene/" + filename;
	loadOBJ(this->filename.c_str(), out_vertices, out_normals, out_uvs);

	glm::vec3 v1, v2, v3, n1, n2, n3;
	
	if (
		(
			((out_normals.size() > 0) && (out_normals.size() == out_vertices.size()))
			||
			(out_normals.size() == 0)
		)
		&&
			(out_vertices.size()%3 == 0)
		)
	{
		if (out_normals.size() > 0)
		{
			std::cout << "Triangle has its own normals at each point..." << std::endl;
			for (int i = 0; i < out_vertices.size(); i += 3)
			{
				v1 = out_vertices[i];
				v2 = out_vertices[i + 1];
				v3 = out_vertices[i + 2];
				
				n1 = out_normals[i];
				n2 = out_normals[i + 1];
				n3 = out_normals[i + 2];

				this->triangles.emplace_back(new MeshTriangle(v1, v2, v3, n1, n2, n3,
					this->amb_col, this->diff_col, this->spe_col, this->shininess));
			}
			has_pt_normals = true;
		}
		else
		{
			for (int i = 0; i < out_vertices.size(); i += 3)
			{
				v1 = out_vertices[i];
				v2 = out_vertices[i + 1];
				v3 = out_vertices[i + 2];
				this->triangles.emplace_back(new Triangle(v1, v2, v3,
					this->amb_col, this->diff_col, this->spe_col, this->shininess));
			}

			has_pt_normals = false;
		}
	}
}

void Mesh::print()
{
	if (this->has_pt_normals)
	{
		for (int i = 0; i < this->triangles.size(); i++)
		{
			(static_cast<MeshTriangle*>(this->triangles[i]))->print();
		}
	}
	else
	{
		for (int i = 0; i < this->triangles.size(); i++)
		{
			this->triangles[i]->print();
		}
	}
}

// generate AABB for mesh
void Mesh::genBoundingBox()
{
	// retrieve the min & max xyz points
	glm::vec3 max = glm::vec3(-INFINITY, -INFINITY, -INFINITY);
	glm::vec3 min = glm::vec3(INFINITY, INFINITY, INFINITY);

	for (int i = 0; i < (this->triangles.size()); i++)
	{
		// v1 comparison with max x,y,z
		if (triangles[i]->v1.x > max.x)
			max.x = triangles[i]->v1.x;
		if (triangles[i]->v1.y > max.y)
			max.y = triangles[i]->v1.y;
		if (triangles[i]->v1.z > max.z)
			max.z = triangles[i]->v1.z;

		// v1 comparison with min x,y,z
		if (triangles[i]->v1.x < min.x)
			min.x = triangles[i]->v1.x;
		if (triangles[i]->v1.y < min.y)
			min.y = triangles[i]->v1.y;
		if (triangles[i]->v1.z < min.z)
			min.z = triangles[i]->v1.z;

		// v2 comparison with max x,y,z
		if (triangles[i]->v2.x > max.x)
			max.x = triangles[i]->v2.x;
		if (triangles[i]->v2.y > max.y)
			max.y = triangles[i]->v2.y;
		if (triangles[i]->v2.z > max.z)
			max.z = triangles[i]->v2.z;

		// v2 comparison with min x,y,z
		if (triangles[i]->v2.x < min.x)
			min.x = triangles[i]->v2.x;
		if (triangles[i]->v2.y < min.y)
			min.y = triangles[i]->v2.y;
		if (triangles[i]->v2.z < min.z)
			min.z = triangles[i]->v2.z;

		// v3 comparison with max x,y,z
		if (triangles[i]->v3.x > max.x)
			max.x = triangles[i]->v3.x;
		if (triangles[i]->v3.y > max.y)
			max.y = triangles[i]->v3.y;
		if (triangles[i]->v3.z > max.z)
			max.z = triangles[i]->v3.z;

		// v3 comparison with min x,y,z
		if (triangles[i]->v3.x < min.x)
			min.x = triangles[i]->v3.x;
		if (triangles[i]->v3.y < min.y)
			min.y = triangles[i]->v3.y;
		if (triangles[i]->v3.z < min.z)
			min.z = triangles[i]->v3.z;
	}
	this->boundingBox = BoundingBox(max, min);
}