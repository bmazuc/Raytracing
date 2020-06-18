#include "pch.h"
#include "MovingSphere.h"


MovingSphere::MovingSphere(Vector3 _center0, Vector3 _center1, float t0, float t1, float _radius, std::shared_ptr<Material> _material)
{

}

Vector3 MovingSphere::GetCenter(float time) const
{
	Vector3 offset = (center1 - center0) * ((time - time0) / (time1 - time0));
	return center0 + offset;
}

bool MovingSphere::Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const
{
	Vector3 oc = r.origin - GetCenter(r.time);
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
		Vector3 outwardNormal = (info.point - GetCenter(r.time)) / radius;
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
		Vector3 outwardNormal = (info.point - GetCenter(r.time)) / radius;
		info.isFrontFace = Vector3::DotProduct(r.direction, outwardNormal) < 0;
		info.normal = info.isFrontFace ? outwardNormal : -outwardNormal;
		info.material = material;
		return true;
	}

	return false;
}