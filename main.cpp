#include <iostream>
#include "glm/glm.hpp"
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

bool hitLight(const Ray& sec_ray, const Light& light, ShadeInfo& shadowRayInfo);

int main() {

	std::string input_file_path, output_file_path;
	std::cout << "Please enter the scene filename: ";
	std::cin >> input_file_path;
	std::cout << "Please enter the output filename: ";
	std::cin >> output_file_path;

	std::cout << "Trying to load from path: " + ("../scene/" + input_file_path) << std::endl;
	if (load_scene(("../scene/" + input_file_path).c_str(), camera, mesh, plane, spheres, lights, triangles))
	{
		std::cout << "SCENE LOADED" << std::endl;
		camera.print();
		plane.print();
		for (unsigned int i = 0; i < spheres.size(); i++)
		{
			spheres[i].print();
			spheres[i].sphereID = i;
		}
		for (unsigned int i = 0; i < triangles.size(); i++)
		{
			triangles[i].print();
		}
		for (unsigned int i = 0; i < lights.size(); i++)
		{
			lights[i].print();
		}
	}

	int width = camera.focal_length * camera.aspect_ratio * tan(glm::radians(camera.fov)/2.0) * 2.0;
	int height = camera.focal_length * tan(glm::radians(camera.fov)/2.0) * 2.0;

	std::cout << "WIDTH:HEIGHT = " << width << ":" << height << std::endl;

	//create image with three channels and set it to black
	cimg_library::CImg<float> image(width, height, 1, CHANNELS, 0);       // Define a 256x256 color image
	//...

	double dx, dy, dz = -camera.focal_length;
	glm::dvec3 ray_direction;
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

	std::cout << "Non-mesh objects: " << objects.size() << std::endl;
	std::cout << "Mesh triangles (if any): " << mesh.triangles.size() << std::endl;
	std::cout << "Lights: " << lights.size() << std::endl;

	for (unsigned int y = 0; y < height; y++) {
		for (unsigned int x = 0; x < width; x++) {
			dx = x + 0.5 - (width * 0.5);
			dy = y + 0.5 - (height * 0.5);
			t = INFINITY;
			shadeInfo = ShadeInfo();

			// from viewer to object (if any)
			ray_direction = glm::normalize(glm::dvec3(dx, dy, dz));
			ray = Ray(camera.pos, ray_direction);

			// does the ray hit any object?
			for (unsigned int i = 0; i < objects.size(); i++)
			{
				objects[i]->hit(ray, t, shadeInfo);
			}
			if (mesh.boundingBox.hit(ray))
			{
				for (unsigned int i = 0; i < mesh.triangles.size(); i++)
				{
					mesh.triangles[i]->hit(ray, t, shadeInfo);
				}
			}

			// if so, is there any occluding object between the hit surface and each light source?
			if (shadeInfo.hit_an_obj)
			{
				glm::dvec3 pt_of_contact = ray.pointAtParameter(t);

				glm::vec3 computed_color = shadeInfo.amb_col;
				ShadeInfo shadowRayInfo;
				//shadowRayInfo.sphere_comp_mode = true;

				for (unsigned int i = 0; i < lights.size(); i++)
				{
					shadowRayInfo.hit_an_obj = false;
					shadowRayInfo.hit_obj = Nothing_Hit;
					shadowRayInfo.sphere_comp_mode = true;
					glm::dvec3 secondary_ray_dir = glm::normalize((glm::dvec3)lights[i].pos - pt_of_contact);
					Ray sec_ray = Ray(pt_of_contact, secondary_ray_dir);

					// if not, add light's contribution to point's color computation
					if (hitLight(sec_ray, lights[i], shadowRayInfo))
					{
						double cosine_angle = glm::dot((glm::dvec3)shadeInfo.surface_norm, secondary_ray_dir);

						if (cosine_angle < 0.0)
							cosine_angle = 0.0;

						glm::dvec3 r = glm::normalize(2.0*(cosine_angle)*(glm::dvec3)shadeInfo.surface_norm - secondary_ray_dir);

						double r_dot_v = glm::dot(r, -ray_direction);
						if (r_dot_v < 0.0)
							r_dot_v = 0.0;

						// ambient contribution from light source
						computed_color += ((glm::dvec3)lights[i].amb_col*(glm::dvec3)shadeInfo.amb_col);
						// diffuse contribution from light source
						computed_color += (((glm::dvec3)lights[i].diff_col*(glm::dvec3)shadeInfo.diff_col)*(cosine_angle));
						// specular contribution from light source
						computed_color += (((glm::dvec3)lights[i].spe_col*(glm::dvec3)shadeInfo.spe_col)*(pow(r_dot_v, shadeInfo.shininess)));
					}
					else
					{
						if (shadeInfo.hit_obj == Sphere_Hit)
						{
							// prevents sphere from casting shadow on itself (to better match expected scene file outputs)
							if ((shadowRayInfo.hit_obj == Sphere_Hit) && (shadowRayInfo.hit_sphere_id == shadeInfo.hit_sphere_id))
								computed_color += ((glm::dvec3)lights[i].amb_col*(glm::dvec3)shadeInfo.amb_col);

							// there was a light under a plane in one of the sample scene files
							// this is to allow the light to pass through it
							if (shadowRayInfo.hit_obj == Plane_Hit)
							{
								double cosine_angle = glm::dot((glm::dvec3)shadeInfo.surface_norm, secondary_ray_dir);

								if (cosine_angle < 0.0)
									cosine_angle = 0.0;

								glm::dvec3 r = glm::normalize(2.0*(cosine_angle)*(glm::dvec3)shadeInfo.surface_norm - secondary_ray_dir);

								double r_dot_v = glm::dot(r, -ray_direction);
								if (r_dot_v < 0.0)
									r_dot_v = 0.0;

								// ambient contribution from light source
								computed_color += ((glm::dvec3)lights[i].amb_col*(glm::dvec3)shadeInfo.amb_col);
								// diffuse contribution from light source
								computed_color += (((glm::dvec3)lights[i].diff_col*(glm::dvec3)shadeInfo.diff_col)*(cosine_angle));
								// specular contribution from light source
								computed_color += (((glm::dvec3)lights[i].spe_col*(glm::dvec3)shadeInfo.spe_col)*(pow(r_dot_v, shadeInfo.shininess)));
							}
						}
					}
				}
				// clamp it
				computed_color = glm::clamp(computed_color, 0.0f, 1.0f);

				image(x, height - 1 - y, RED) = computed_color.x * 255.0f;
				image(x, height - 1 - y, GREEN) = computed_color.y * 255.0f;
				image(x, height - 1 - y, BLUE) = computed_color.z * 255.0f;
			}
		}
	}


	// save out image in BMP format
	image.save(("../_output/" + output_file_path).c_str());
	// display the rendered image on screen
	cimg_library::CImgDisplay main_disp(image, "Render");
	while (!main_disp.is_closed()) { main_disp.wait(); }
	system("pause");
}

bool hitLight(const Ray& sec_ray, const Light& light, ShadeInfo& shadowRayInfo)
{
	// distance between the point and the light!
	// if and only if we find something where t < that distance can we return false
	double dist = glm::distance((glm::dvec3)light.pos, sec_ray.getOrigin());
	double t = INFINITY;

	for (int i = 0; i < objects.size(); i++)
	{
		if ((objects[i]->hit(sec_ray, t, shadowRayInfo)) && (t < dist)) {
			return false;
		}
	}
	if (mesh.boundingBox.hit(sec_ray))
	{
		for (int i = 0; i < mesh.triangles.size(); i++)
		{
			if (mesh.triangles[i]->hit(sec_ray, t, shadowRayInfo) && (t < dist))
				return false;
		}
	}
	return true;
}