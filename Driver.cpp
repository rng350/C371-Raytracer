#include <iostream>
#include "CImg.h"
#include "Ray.h"
#include "scene_loader.h"

#define WIDTH 800.0f
#define HEIGHT 600.0f
#define CHANNELS 3
#define RED 0
#define GREEN 1
#define BLUE 2

glm::vec3 color(const Ray& r)
{
	glm::vec3 unit_direction = glm::normalize(r.getDirection());
	float t = 0.5*(unit_direction.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

int main() {
	// 
	//create image with three channels and set it to black
	cimg_library::CImg<float> image(WIDTH, HEIGHT, 1, CHANNELS, 0);       // Define a 256x256 color image
	//...
	//...
	glm::vec3 lower_left_corner = glm::vec3(-2.0f, -1.0f, -1.0f);
	glm::vec3 horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
	glm::vec3 vertical = glm::vec3(0.0f, 2.0f, 0.0f);
	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);

	Camera camera;
	Plane plane;
	Mesh mesh;
	std::vector<Sphere> spheres;
	std::vector<Triangle> triangles;
	std::vector<Light> lights;

	if (load_scene("scene/scenefish.txt", camera, mesh, plane, spheres, lights, triangles))
	{
		std::cout << "SCENE LOADED" << std::endl;
		camera.print();
		plane.print();
		for (int i = 0; i < spheres.size(); i++)
		{
			spheres[i].print();
		}
		for (int i = 0; i < triangles.size(); i++)
		{
			triangles[i].print();
		}
		for (int i = 0; i < lights.size(); i++)
		{
			lights[i].print();
		}
		std::cout << "Mesh triangles: " << mesh.triangles.size() << std::endl;
		mesh.print();
	}

	for (float y = 599.0f; y > -1.0f; y--) {
		for (float x = 0; x < WIDTH; x++) {
			float u = (x / WIDTH);
			float v = (y / HEIGHT);

			Ray r = Ray(origin, lower_left_corner + u * horizontal + v * vertical);
			glm::vec3 col = color(r);

			image(x, (599.0f - y), RED) = col.x * 255.0f;
			image(x, (599.0f - y), GREEN) = col.y * 255.0f;
			image(x, (599.0f - y), BLUE) = col.z * 255.0f;
		}
	}
	//...
	//...
	// save out image in BMP format
	//image.save("render.bmp");
	// display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) { main_disp.wait(); }
	system("pause");
}