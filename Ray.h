#include "glm/glm.hpp"

#ifndef RAYH
#define RAYH
class Ray
{
	public:
		Ray() {}
		Ray(const glm::dvec3& origin, const glm::dvec3& dir) { this->origin = origin; this->dir = dir; }
		~Ray() {};
		glm::dvec3 getOrigin() const { return this->origin; }
		glm::dvec3 getDirection() const { return this->dir; }
		glm::dvec3 pointAtParameter(double t) const { return this->origin + (t*this->dir); }
		glm::dvec3 origin, dir;
};
#endif