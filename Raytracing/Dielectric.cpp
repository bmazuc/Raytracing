#include "pch.h"
#include "Dielectric.h"
#include "MathUtility.h"

Dielectric::Dielectric(float _refractionIndex)
	: Material(), refractionIndex(_refractionIndex)
{
}

bool Dielectric::Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const
{
	attenuation = Vector3(1.f, 1.f, 1.f);
	float refractionIndiceRatio = info.isFrontFace ? (refractionIndiceRatio = 1.f / refractionIndex) : refractionIndiceRatio = refractionIndex;

	Vector3 unitDir = rayIn.direction.Normalized();

	float cosTheta = fmin(Vector3::DotProduct(-unitDir, info.normal), 1.f);
	float sinTheta = std::sqrt(1.f - cosTheta * cosTheta);
	if (refractionIndiceRatio * sinTheta > 1.f)
	{
		Vector3 reflected = Vector3::Reflect(unitDir, info.normal);
		scattered = Ray(info.point, reflected);
		return true;
	}

	float reflectProb = Schlick(cosTheta, refractionIndiceRatio);
	if (randomFloat() < reflectProb)
	{
		Vector3 reflected = Vector3::Reflect(unitDir, info.normal);
		scattered = Ray(info.point, reflected);
		return true;
	}

	Vector3 refracted = Vector3::Refract(unitDir, info.normal, refractionIndiceRatio);
	scattered = Ray(info.point, refracted);
	return true;
}