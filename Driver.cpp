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


Camera camera;
Plane plane;
Mesh mesh;
std::vector<Sphere> spheres;
std::vector<Triangle> triangles;
std::vector<Light> lights;
std::vector<GeometricObject*> objects;

bool hitLight(const Ray& sec_ray, const Light& light);

int main() {

	std::string input_file_path, output_file_path;
	std::cout << "Please enter the scene filename: ";
	std::cin >> input_file_path;
	std::cout << "Please enter the output filename: ";
	std::cin >> output_file_path;

	if (load_scene(("scene/" + input_file_path).c_str(), camera, mesh, plane, spheres, lights, triangles))
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

	float dx, dy, dz = -camera.focal_length;
	glm::vec3 ray_direction;
	double t;
	Ray ray;
	ShadeInfo shadeInfo;

	objects.push_back(&plane);
	for (int i = 0; i < spheres.size(); i++)
	{
		objects.push_back(&spheres[i]);
	}
	for (int i = 0; i < triangles.size(); i++)
	{
		objects.push_back(&triangles[i]);
	}

	int i = 0;

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			dx = x + 0.5 - (width * 0.5);
			dy = y + 0.5 - (height * 0.5);
			t = INFINITY;
			shadeInfo = ShadeInfo();

			ray_direction = glm::normalize(glm::vec3(dx, dy, dz));
			ray = Ray(camera.pos, ray_direction);

			for (int i = 0; i < objects.size(); i++)
			{
				objects[i]->hit(ray, t, shadeInfo);
			}
			for (int i = 0; i < mesh.triangles.size(); i++)
			{
				mesh.triangles[i]->hit(ray, t, shadeInfo);
			}
			if (shadeInfo.hit_an_obj)
			{
				glm::vec3 pt_of_contact = camera.pos + (float)t*ray_direction;

				glm::vec3 secondary_ray_dir = glm::normalize(lights[i].pos - pt_of_contact);
				Ray sec_ray = Ray(pt_of_contact, secondary_ray_dir);

				glm::vec3 computed_color = shadeInfo.amb_col;

				if (hitLight(sec_ray, lights[i]))
				{
					float l_dot_n = glm::dot(shadeInfo.surface_norm, secondary_ray_dir);
					if (l_dot_n < 0.0f)
						l_dot_n = 0.0f;
					glm::vec3 r = 2.0f*(l_dot_n)*shadeInfo.surface_norm - secondary_ray_dir;
					float r_dot_v = glm::dot(r, ray_direction);
					if (r_dot_v < 0.0f)
						r_dot_v = 0.0f;
					computed_color += lights[i].col * (shadeInfo.diff_col*(l_dot_n)) + shadeInfo.spe_col * (pow(r_dot_v, shadeInfo.shininess));
				}

				computed_color = glm::clamp(computed_color, 0.0f, 1.0f);

				image(x, height - 1 - y, RED) = computed_color.x * 255.0f;
				image(x, height - 1 - y, GREEN) = computed_color.y * 255.0f;
				image(x, height - 1 - y, BLUE) = computed_color.z * 255.0f;
			}
			
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
	image.save(("_output/" + output_file_path).c_str());
	// display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) { main_disp.wait(); }
	system("pause");
}

bool hitLight(const Ray& sec_ray, const Light& light)
{
	double t = INFINITY;

	ShadeInfo dummy = ShadeInfo();

	// we only care if it hits ANY object along the way
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i]->hit(sec_ray, t, dummy))
			return false;
	}
	for (int i = 0; i < mesh.triangles.size(); i++)
	{
		if (mesh.triangles[i]->hit(sec_ray, t, dummy))
			return false;
	}
	return true;
}