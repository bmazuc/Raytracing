#include "pch.h"
#include "Sphere.h"


Sphere::Sphere(Vector3 _center, float _radius, std::shared_ptr<Material> _material)
	: center(_center), radius(_radius), material(_material)
{
}

bool Sphere::Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const
{
	Vector3 oc = r.origin - center;
	float a = r.direction.LengthSqr();
	float halfB = Vector3::DotProduct(oc, r.direction);
	float c = oc.LengthSqr() - radius * radius;
	float delta = halfB * halfB - a * c;

	if (delta <= 0)
		return false;

	float deltaSqrt = std::sqrt(delta);
	float temp = (-halfB - deltaSqrt) / a;
	
	if (temp < tMax && temp > tMin)
	{
		info.t = temp;
		info.point = r.At(info.t);
		Vector3 outwardNormal = (info.point - center) / radius;
		info.isFrontFace = Vector3::DotProduct(r.direction, outwardNormal) < 0;
		info.normal = info.isFrontFace ? outwardNormal : -outwardNormal;
		info.material = material;
		return true;
	}

	temp = (-halfB + deltaSqrt) / a;

	if (temp < tMax && temp > tMin)
	{
		info.t = temp;
		info.point = r.At(info.t);
		Vector3 outwardNormal = (info.point - center) / radius;
		info.isFrontFace = Vector3::DotProduct(r.direction, outwardNormal) < 0;
		info.normal = info.isFrontFace ? outwardNormal : -outwardNormal;
		info.material = material;
		return true;
	}

	return false;
}