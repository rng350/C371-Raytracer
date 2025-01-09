#pragma once
#ifndef BOUND_BOX
#define BOUND_BOX
#include "glm/glm.hpp"
#include "Ray.h"

// An AABB, in case I'm faced with a Heracles.obj-like monstruosity
// Crude, but better than nothing
class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(glm::vec3 max, glm::vec3 min);
	~BoundingBox();
	bool hit(const Ray& ray);
	glm::vec3 max, min;
};
#endif