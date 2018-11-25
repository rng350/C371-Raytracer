#include <iostream>
#include "CImg.h"
#include "Ray.h"
#include "scene_loader.h"

#define CHANNELS 3
#define RED 0
#define GREEN 1
#define BLUE 2
#define INV_PI 0.31830988618379067153776752674503
#define TO_RADIANS 0.01745329251994329576923690768489

glm::vec3 color(const Ray& r)
{
	glm::vec3 unit_direction = glm::normalize(r.getDirection());
	float t = 0.5*(unit_direction.y + 1.0f);
	return (1.0f - t) * glm::vec3(1.0f, 1.0f, 1.0f) + t * glm::vec3(0.5f, 0.7f, 1.0f);
}

int main() {
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
		for (unsigned int i = 0; i < spheres.size(); i++)
		{
			spheres[i].print();
		}
		for (unsigned int i = 0; i < triangles.size(); i++)
		{
			triangles[i].print();
		}
		for (unsigned int i = 0; i < lights.size(); i++)
		{
			lights[i].print();
		}
		std::cout << "Mesh triangles: " << mesh.triangles.size() << std::endl;

		//mesh.print();

		/*
		if (mesh.has_pt_normals)
			(static_cast<MeshTriangle*>(mesh.triangles[0]))->print();
		else
			mesh.triangles[0]->print();
		*/


	}

	int width = camera.focal_length * camera.aspect_ratio * tan(glm::radians(camera.fov)/2.0) * 2.0;
	int height = camera.focal_length * tan(glm::radians(camera.fov)/2.0) * 2.0;

	std::cout << "WIDTH:HEIGHT = " << width << ":" << height << std::endl;

	//create image with three channels and set it to black
	cimg_library::CImg<float> image(width, height, 1, CHANNELS, 0);       // Define a 256x256 color image
	//...
	//...
	glm::vec3 lower_left_corner = glm::vec3(-2.0f, -1.0f, -1.0f);
	glm::vec3 horizontal = glm::vec3(4.0f, 0.0f, 0.0f);
	glm::vec3 vertical = glm::vec3(0.0f, 2.0f, 0.0f);
	glm::vec3 origin = glm::vec3(0.0f, 0.0f, 0.0f);


	/*
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
	*/

	/*
	for (float y = 0; y < height; y++) {
		for (float x = 0; x < width; x++) {

			// red at lowest y & x corner
			if ((y < height / 2.0) && (x < width / 3.0))
			{
				image(x, height - 1 - y, RED) = 1.0 * 255.0f;
				image(x, height - 1 - y, GREEN) = 0.0 * 255.0f;
				image(x, height - 1 - y, BLUE) = 0.0 * 255.0f;
			}

			// green at lowest y, highest x corner
			if ((y < height / 3.0) && (x > 2.0 * width / 3.0))
			{
				image(x, height - 1 - y, RED) = 0.0 * 255.0f;
				image(x, height - 1 - y, GREEN) = 1.0 * 255.0f;
				image(x, height - 1 - y, BLUE) = 0.0 * 255.0f;
			}

			// grey at  highest y, lowest x corner
			if ((y > 2.0 * height / 3.0) && (x < width / 3.0))
			{
				image(x, height - 1 - y, RED) = 0.5 * 255.0f;
				image(x, height - 1 - y, GREEN) = 0.5 * 255.0f;
				image(x, height - 1 - y, BLUE) = 0.5 * 255.0f;
			}

			// blue at highest y, highest x corner
			if ((y > 2.0 * height / 3.0) && (x > 2.0 * width / 3.0))
			{
				image(x, height - 1 - y, RED) = 0.0 * 255.0f;
				image(x, height - 1 - y, GREEN) = 0.0 * 255.0f;
				image(x, height - 1 - y, BLUE) = 1.0 * 255.0f;
			}
		}
	}
	*/

	float dx, dy, dz = -camera.focal_length;
	glm::vec3 ray_direction;
	double t;
	Ray ray;
	ShadeInfo shadeInfo;

	std::vector<GeometricObject*> objects;
	objects.push_back(&plane);
	for (int i = 0; i < spheres.size(); i++)
	{
		objects.push_back(&spheres[i]);
	}

	int i = 0;

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			dx = x + 0.5 - (width * 0.5);
			dy = y + 0.5 - (height * 0.5);
			t = INFINITY;

			ray_direction = glm::normalize(glm::vec3(dx, dy, dz));
			ray = Ray(camera.pos, ray_direction);

			/*
			*/
			if (plane.hit(ray,t,shadeInfo))
			{
				//std::cout << ++i << "xy:<" << x << "," << (height - 1 - y) << ">";
				//std::cout << ++i << "ray_dir:<" << ray.getDirection().x << "," << ray.getDirection().y << "," << ray.getDirection().z << ">" << std::endl;
				image(x, height - 1 - y, RED) = 0.0 * 255.0f;
				image(x, height - 1 - y, GREEN) = 1.0 * 255.0f;
				image(x, height - 1 - y, BLUE) = 0.0 * 255.0f;
			}

			for (int i = 0; i < spheres.size(); i++)
			{
				if (spheres[i].hit(ray, t, shadeInfo))
				{
					image(x, height - 1 - y, RED) = 1.0 * 255.0f;
					image(x, height - 1 - y, GREEN) = 0.0 * 255.0f;
					image(x, height - 1 - y, BLUE) = 0.0 * 255.0f;
				}
			}
			for (int i = 0; i < mesh.triangles.size(); i++)
			{
				if (mesh.triangles[i]->hit(ray, t, shadeInfo))
				{
					std::cout << "h!";
					image(x, height - 1 - y, RED) = 0.0 * 255.0f;
					image(x, height - 1 - y, GREEN) = 0.0 * 255.0f;
					image(x, height - 1 - y, BLUE) = 1.0 * 255.0f;
					break;
				}
			}
			/*
			*/

			//if ((x == 30) && x == y)
			//	std::cout << "Ray @ WANTED: pos:<" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ">, dir:<" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ">" << std::endl;
			
			if ((x == 0) && (y == 1))
			{
				std::cout << "Ray @ bottom left: pos:<" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ">, dir:<" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ">" << std::endl;
			}

			if ((x == (width-1)) && (y == 1))
				std::cout << "Ray @ bottom right: pos:<" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ">, dir:<" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ">" << std::endl;

			if ((x == 0) && (y == (height-1)))
				std::cout << "Ray @ top left: pos:<" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ">, dir:<" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ">" << std::endl;

			if ((x == (width - 1)) && y == (height-1))
				std::cout << "Ray @ top right: pos:<" << ray.origin.x << "," << ray.origin.y << "," << ray.origin.z << ">, dir:<" << ray.dir.x << "," << ray.dir.y << "," << ray.dir.z << ">" << std::endl;
			
		}
	}


	//...
	//...
	// save out image in BMP format
	image.save("withPlane.bmp");
	// display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) { main_disp.wait(); }
	system("pause");
}