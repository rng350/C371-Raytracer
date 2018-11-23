#include "GeometricObject.h"


GeometricObject::GeometricObject()
{}
GeometricObject::GeometricObject(glm::vec3 amb_col, glm::vec3 diff_col, glm::vec3 spe_col, float shininess)
{
	this->amb_col = amb_col;
	this->diff_col = diff_col;
	this->spe_col = spe_col;
	this->shininess = shininess;
}

GeometricObject::~GeometricObject() {}