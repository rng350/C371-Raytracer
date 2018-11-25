// used provided obj loader as a base

#include "Camera.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Plane.h"
#include "Light.h"
#include "Mesh.h"
#include <cstring>
#include <stdlib.h>

bool load_scene(
	const char * path,
	Camera & out_camera,
	Mesh & out_mesh,
	Plane & out_plane,
	std::vector<Sphere> & out_spheres,
	std::vector<Light> & out_lights,
	std::vector<Triangle> & out_triangles
	)
{
	std::vector<Sphere> temp_spheres;
	std::vector<Light> temp_lights;
	std::vector<Triangle> temp_triangles;

	FILE * file;
    int _errno = fopen_s(&file, path, "r");
	if (_errno != 0)
	{
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	int num_of_obj = 0, count = 0;
	// read the first word of the line
	int res = fscanf_s(file, "%d\n", &num_of_obj);
	if (res == EOF)
		return false;

	printf("Number of objects: %d\n", num_of_obj);

	while (1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s\n", &lineHeader,128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		printf("%s\n", lineHeader);

		if (strcmp(lineHeader, "camera") == 0)
		{
			printf("GOT CAMERA!\n");
			// initialize attributes with invalid values
			glm::vec3 pos;
			float fov = -1;
			float focal_length = -1;
			float aspect_ratio = -1;

			// scan through given attributes in file
			int num_of_attribs = 4;
			for (int i = 0; i < num_of_attribs; i++)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(file, "%s", lineHeader,128);
				if (res == EOF)
					break; // EOF = End Of File. Quit the loop.
				
				if (strcmp(lineHeader, "pos:") == 0)
					fscanf_s(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
				else if (strcmp(lineHeader, "fov:") == 0)
					fscanf_s(file, "%f\n", &fov);
				else if (strcmp(lineHeader, "f:") == 0)
					fscanf_s(file, "%f\n", &focal_length);
				else if (strcmp(lineHeader, "a:") == 0)
					fscanf_s(file, "%f\n", &aspect_ratio);
				else break;
			}
			// if all the required attributes are scanned, then load them
			if ((fov != -1) && (focal_length != -1) && (aspect_ratio != -1))
			{
				out_camera = Camera(pos, fov, focal_length, aspect_ratio);
				count++;
			}
		}
		else if (strcmp(lineHeader, "plane") == 0)
		{
			printf("GOT PLANE!\n");
			glm::vec3 normal;
			glm::vec3 pos;
			glm::vec3 amb_col;
			glm::vec3 diff_col;
			glm::vec3 spe_col;
			float shininess = -1;

			// scan through given attributes in file
			int num_of_attribs = 6;
			for (int i = 0; i < num_of_attribs; i++)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(file, "%s", lineHeader,128);
				if (res == EOF)
					break; // EOF = End Of File. Quit the loop.
				
				if (strcmp(lineHeader, "pos:") == 0)
					fscanf_s(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
				else if (strcmp(lineHeader, "nor:") == 0)
					fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
				else if (strcmp(lineHeader, "amb:") == 0)
					fscanf_s(file, "%f %f %f\n", &amb_col.x, &amb_col.y, &amb_col.z);
				else if (strcmp(lineHeader, "dif:") == 0)
					fscanf_s(file, "%f %f %f\n", &diff_col.x, &diff_col.y, &diff_col.z);
				else if (strcmp(lineHeader, "spe:") == 0)
					fscanf_s(file, "%f %f %f\n", &spe_col.x, &spe_col.y, &spe_col.z);
				else if (strcmp(lineHeader, "shi:") == 0)
					fscanf_s(file, "%f\n", &shininess);
				else break;
			}
			if ((shininess != -1))
			{
				out_plane = Plane(pos, normal, amb_col, diff_col, spe_col, shininess);
				count++;
			}
		}
		else if (strcmp(lineHeader, "sphere") == 0)
		{
			printf("GOT SPHERE!\n");
			glm::vec3 pos;
			float radius = -1;
			glm::vec3 amb_col;
			glm::vec3 diff_col;
			glm::vec3 spe_col;
			float shininess = -1;

			// scan through given attributes in file
			int num_of_attribs = 6;
			for (int i = 0; i < num_of_attribs; i++)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(file, "%s", lineHeader,128);
				if (res == EOF)
					break; // EOF = End Of File. Quit the loop.
				
				if (strcmp(lineHeader, "pos:") == 0)
					fscanf_s(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
				else if (strcmp(lineHeader, "rad:") == 0)
					fscanf_s(file, "%f\n", &radius);
				else if (strcmp(lineHeader, "amb:") == 0)
					fscanf_s(file, "%f %f %f\n", &amb_col.x, &amb_col.y, &amb_col.z);
				else if (strcmp(lineHeader, "dif:") == 0)
					fscanf_s(file, "%f %f %f\n", &diff_col.x, &diff_col.y, &diff_col.z);
				else if (strcmp(lineHeader, "spe:") == 0)
					fscanf_s(file, "%f %f %f\n", &spe_col.x, &spe_col.y, &spe_col.z);
				else if (strcmp(lineHeader, "shi:") == 0)
					fscanf_s(file, "%f\n", &shininess);
				else break;
			}
			if ((shininess != -1) && (radius != -1))
			{
				temp_spheres.push_back(Sphere(pos, radius, amb_col, diff_col, spe_col, shininess));
				count++;
			}
		}
		else if (strcmp(lineHeader, "mesh") == 0)
		{
			printf("GOT MESH!\n");
			// (...)
			std::string filename = "";
			glm::vec3 amb_col;
			glm::vec3 diff_col;
			glm::vec3 spe_col;
			float shininess = -1;

			// scan through given attributes in file
			int num_of_attribs = 5;
			for (int i = 0; i < num_of_attribs; i++)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(file, "%s", lineHeader,128);
				if (res == EOF)
					break; // EOF = End Of File. Quit the loop.
				if (strcmp(lineHeader, "file:") == 0)
				{
					char scene_file[50];
					fscanf_s(file, "%s\n", &scene_file, 50);
					filename = scene_file;
				}
				else if (strcmp(lineHeader, "amb:") == 0)
					fscanf_s(file, "%f %f %f\n", &amb_col.x, &amb_col.y, &amb_col.z);
				else if (strcmp(lineHeader, "dif:") == 0)
					fscanf_s(file, "%f %f %f\n", &diff_col.x, &diff_col.y, &diff_col.z);
				else if (strcmp(lineHeader, "spe:") == 0)
					fscanf_s(file, "%f %f %f\n", &spe_col.x, &spe_col.y, &spe_col.z);
				else if (strcmp(lineHeader, "shi:") == 0)
					fscanf_s(file, "%f\n", &shininess);
				else break;
			}
			if ((filename.length() > 0) && (shininess != -1))
			{
				out_mesh = Mesh(filename, amb_col, diff_col, spe_col, shininess);
				count++;
			}
		}
		else if (strcmp(lineHeader, "light") == 0)
		{
			printf("GOT LIGHT!\n");
			glm::vec3 pos;
			glm::vec3 col;

			// scan through given attributes in file
			int num_of_attribs = 2;
			for (int i = 0; i < num_of_attribs; i++)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(file, "%s", lineHeader,128);
				if (res == EOF)
					break; // EOF = End Of File. Quit the loop.
				
				if (strcmp(lineHeader, "pos:") == 0)
					fscanf_s(file, "%f %f %f\n", &pos.x, &pos.y, &pos.z);
				else if (strcmp(lineHeader, "col:") == 0)
					fscanf_s(file, "%f %f %f\n", &col.x, &col.y, &col.z);
				else break;
			}
			temp_lights.push_back(Light(pos, col));
			count++;
		}
		else if (strcmp(lineHeader, "triangle") == 0)
		{
			printf("GOT TRIANGLE!\n");
			glm::vec3 v1;
			glm::vec3 v2;
			glm::vec3 v3;
			glm::vec3 amb_col;
			glm::vec3 diff_col;
			glm::vec3 spe_col;
			float shininess = -1;

			// scan through given attributes in file
			int num_of_attribs = 7;
			for (int i = 0; i < num_of_attribs; i++)
			{
				char lineHeader[128];
				// read the first word of the line
				int res = fscanf_s(file, "%s", lineHeader,128);
				if (res == EOF)
					break; // EOF = End Of File. Quit the loop.
				
				if (strcmp(lineHeader, "v1:") == 0)
					fscanf_s(file, "%f %f %f\n", &v1.x, &v1.y, &v1.z);
				else if (strcmp(lineHeader, "v2:") == 0)
					fscanf_s(file, "%f %f %f\n", &v2.x, &v2.y, &v2.z);
				else if (strcmp(lineHeader, "v3:") == 0)
					fscanf_s(file, "%f %f %f\n", &v3.x, &v3.y, &v3.z);
				else if (strcmp(lineHeader, "amb:") == 0)
					fscanf_s(file, "%f %f %f\n", &amb_col.x, &amb_col.y, &amb_col.z);
				else if (strcmp(lineHeader, "dif:") == 0)
					fscanf_s(file, "%f %f %f\n", &diff_col.x, &diff_col.y, &diff_col.z);
				else if (strcmp(lineHeader, "spe:") == 0)
					fscanf_s(file, "%f %f %f\n", &spe_col.x, &spe_col.y, &spe_col.z);
				else if (strcmp(lineHeader, "shi:") == 0)
					fscanf_s(file, "%f\n", &shininess);
				else break;
			}
			if ((shininess != -1))
			{
				temp_triangles.push_back(Triangle(v1, v2, v3, amb_col, diff_col, spe_col, shininess));
				count++;
			}
		}
		else{
			char clear[1000];
			fgets(clear, 1000, file);
		}
	}

	out_spheres = temp_spheres;
	out_lights = temp_lights;
	out_triangles = temp_triangles;

	return (count == num_of_obj);
}