#include "Camera.h"

Camera::Camera()
{
	this->pos = glm::vec3(0.0,0.0,0.0);
	this->fov = -1.0f;
	this->focal_length = -1.0f;
	this->aspect_ratio = -1.0f;
}

Camera::Camera(glm::vec3 pos, float fov, float focal_length, float aspect_ratio)
{
	this->pos = pos;
	this->fov = fov;
	this->focal_length = focal_length;
	this->aspect_ratio = aspect_ratio;
}

void Camera::print()
{
	std::cout << "CAMERA:\n- pos: <" << pos.x << "," << pos.y << "," << pos.z << 
		">\n- fov: "<< fov << "\n- focal: " << focal_length << "\n- a: " << aspect_ratio << std::endl;
}

Camera::~Camera(){}