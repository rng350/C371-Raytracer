#include "glm/glm.hpp"

#ifndef RAYH
#define RAYH
class Ray
{
	public:
		Ray() {}
		Ray(const glm::vec3& origin, const glm::vec3& dir) { this->origin = origin; this->dir = dir; }
		~Ray() {};
		glm::vec3 getOrigin() const { return this->origin; }
		glm::vec3 getDirection() const { return this->dir; }
		glm::vec3 pointAtParameter(float t) const { return this->origin + (t*this->dir); }
		glm::vec3 origin, dir;
};
#endif