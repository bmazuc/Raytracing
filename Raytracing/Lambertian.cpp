#include "pch.h"
#include "Lambertian.h"
#include "MathUtility.h"

Lambertian::Lambertian(Vector3 const& _albedo)
	: Material(), albedo(_albedo)
{
}


bool Lambertian::Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const
{
	Vector3 scatterDirection = info.normal + RandomInUnitSphere();
	scattered = Ray(info.point, scatterDirection);
	attenuation = albedo;
	return true;
}