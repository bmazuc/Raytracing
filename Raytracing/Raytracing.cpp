// Raytracing.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"

#include <iostream>
#include <fstream>
#include <time.h>
#include <thread>
#include <string>
#include <sstream>

#include "Ray.h"
#include "HittableList.h"
#include "Sphere.h"
#include "MovingSphere.h"
#include "Camera.h"
#include "MathUtility.h"

#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"

int const width = 1200;
int const height = 675;
int const samplesPerPixel = 10;
int const maxDepth = 50;

//

int h, w;
float timer;
clock_t t1, t2;
bool display = true;

std::string FormatPercent(int percent)
{
	std::string str;
	if (percent < 10)
		str += '0';

	str += std::to_string(percent);
	str += '%';
	return str;
}

std::string FormatTimer(int hour, int minute, int second)
{
	std::string str;
	if (hour < 10)
		str += '0';
	str += std::to_string(hour);
	str += 'h';
	if (minute < 10)
		str += '0';
	str += std::to_string(minute);
	str += 'm';
	if (second < 10)
		str += '0';
	str += std::to_string(second);
	str += 's';

	return str;
}

void DisplayInfos()
{
	while (display)
	{
		system("cls");
		std::cout << "Scanlines: " << FormatPercent(100.f - (h * 100.f / (height - 1))).c_str() << " (" << h << " Scanlines remaining)." << std::endl;
		std::cout << "Current scanline: " << FormatPercent(w * 100.f / width).c_str() << '.' << std::endl;

		t2 = clock();
		timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
		int hours = timer / 3600.f;
		timer -= (hours * 3600.f);
		
		int minutes, seconds = 0;
		if (timer > 0.f)
		{
			minutes = timer / 60.f;
			timer -= (minutes * 60.f);

			if (timer > 0.f)
			{
				seconds = timer;
			}
		}

		std::cout << "\nElapsed time: " << FormatTimer(hours, minutes, seconds).c_str() << '.' << std::endl;
	}
}

//

Vector3 GetRayColor(Ray const& r, HittableList& world, int depth)
{
	if (depth <= 0)
		return Vector3(0, 0, 0);

	RayHitInfo info;
	if (world.Hit(r, 0.001f, infinity, info))
	{
		Ray scattered;
		Vector3 attenuation;
		if (info.material->Scatter(r, info, attenuation, scattered))
			return attenuation * GetRayColor(scattered, world, depth - 1);
		return Vector3(0, 0, 0);
	}

	Vector3 dir = r.direction.Normalized();
	float t = 0.5*(dir.y() + 1.0);
	return Vector3(1.0f, 1.0f, 1.0f) * (1.0 - t) + Vector3(0.5f, 0.7f, 1.0f) * t;
}

HittableList GenerateRandomScene()
{
	HittableList world;

	std::shared_ptr<Material> groundMaterial = std::make_shared<Lambertian>(Vector3(0.5f, 0.5f, 0.5f));
	world.Add(std::make_shared<Sphere>(Vector3(0.f, -1000.f, 0.f), 1000.f, groundMaterial));

	float chooseMaterial;

	for (int a = -11; a < 11; ++a)
	{
		for (int b = -11; b < 11; ++b)
		{
			chooseMaterial = randomFloat();
			Vector3 center(a + 0.9f * randomFloat(), 0.2f, b + 0.9f * randomFloat());

			if ((center - Vector3(4.f, 0.2f, 0.f)).Length() > 0.9f)
			{
				std::shared_ptr<Material> sphereMaterial;

				if (chooseMaterial < 0.8f) // Diffuse (80%)
				{
					Vector3 albedo = randomVector3() * randomVector3();
					sphereMaterial = std::make_shared<Lambertian>(albedo);
					Vector3 center2 = center + Vector3(0.f, randomFloat(0.f, 0.5f), 0.f);
					world.Add(std::make_shared<MovingSphere>(center, center2, 0.f, 1.f, 0.2f, sphereMaterial));
				}
				else if (chooseMaterial < 0.95f) // Metal (15%)
				{
					Vector3 albedo = randomVector3(0.5f, 1.f);
					float fuzziness = randomFloat(0.f, 0.5f);
					sphereMaterial = std::make_shared<Metal>(albedo, fuzziness);
					world.Add(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
				}
				else // Glass (5%)
				{
					sphereMaterial = std::make_shared<Dielectric>(1.5f);
					world.Add(std::make_shared<Sphere>(center, 0.2f, sphereMaterial));
				}
			}
		}
	}

	std::shared_ptr<Material> material1 = std::make_shared<Dielectric>(1.5f);
	world.Add(std::make_shared<Sphere>(Vector3(0.f, 1.f, 0.f), 1.f, material1));

	std::shared_ptr<Material> material2 = std::make_shared<Lambertian>(Vector3(0.4f, 0.2f, 0.1f));
	world.Add(std::make_shared<Sphere>(Vector3(-4.f, 1.f, 0.f), 1.f, material2));

	std::shared_ptr<Material> material3 = std::make_shared<Metal>(Vector3(0.7f, 0.6f, 0.5f), 0.f);
	world.Add(std::make_shared<Sphere>(Vector3(4.f, 1.f, 0.f), 1.f, material3));

	return world;
}

int main()
{
	std::string imageName;
	std::cout << "Enter image name (None will be Raytracer) :" << std::endl;
	std::getline(std::cin, imageName);

	if (imageName.empty())
		imageName = "Raytracer";
	imageName += ".ppm";

	t1 = clock();

	std::ofstream file;

	file.open(imageName);

	file << "P3\n" << width << ' ' << height << "\n255\n";

	HittableList world = GenerateRandomScene();

	Vector3 lookFrom(13.f, 2.f, 3.f);
	Vector3 lookAt(0.f, 0.f, 0.f);
	Vector3 viewUp(0.f, 1.f, 0.f);
	float distanceToFocus = 10.f;
	float aperture = 0.1f;
	Camera camera(lookFrom, lookAt, viewUp, 20.f, float(width) / height, aperture, distanceToFocus, 0.f, 1.f);

	h = height - 1;

	std::thread displayThread(DisplayInfos);

	for (h; h >= 0; --h)
	{
		for (w = 0; w < width; ++w)
		{
			Vector3 color = Vector3(0.f, 0.f, 0.f);
			for (int s = 0; s < samplesPerPixel; ++s)
			{
				float u = (w + randomFloat()) / (width - 1);
				float v = (h + randomFloat()) / (height - 1);
				Ray r = camera.PointToRay(u, v);
				color += GetRayColor(r, world, maxDepth);
			}

			color /= samplesPerPixel;

			color = Vector3(sqrt(color[0]), sqrt(color[1]), sqrt(color[2])); // Gamma correction

			int ir = int(255.999f * Clamp01(color[0]));
			int ig = int(255.999f * Clamp01(color[1]));
			int ib = int(255.999f * Clamp01(color[2]));

			file << ir << ' ' << ig << ' ' << ib << '\n';
		}
	}

	file.close();
	display = false;
	displayThread.join();

	t2 = clock();
	timer = (float)(t2 - t1) / CLOCKS_PER_SEC;
	int hours = timer / 3600.f;
	timer -= (hours * 3600.f);

	int minutes, seconds = 0;
	if (timer > 0.f)
	{
		minutes = timer / 60.f;
		timer -= (minutes * 60.f);

		if (timer > 0.f)
		{
			seconds = timer;
		}
	}

	std::cout << "\nDone in " << FormatTimer(hours, minutes, seconds).c_str() << '.' << std::endl;

	return 0;
}
