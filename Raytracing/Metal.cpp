#include "pch.h"
#include "Metal.h"
#include "MathUtility.h"

Metal::Metal(Vector3 const& _albedo, float _fuziness)
	: Material(), albedo(_albedo), fuzziness(_fuziness < 1.f ? _fuziness : 1.0f)
{
}


bool Metal::Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const
{
	Vector3 reflected = Vector3::Reflect(rayIn.direction.Normalized(), info.normal);
	scattered = Ray(info.point, reflected + RandomInUnitSphere() * fuzziness);
	attenuation = albedo;
	return (Vector3::DotProduct(scattered.direction, info.normal) > 0);
}
