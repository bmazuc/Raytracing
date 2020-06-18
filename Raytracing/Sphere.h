#ifndef __SPHERE_H_INCLUDED__
#define __SPHERE_H_INCLUDED__

#include <memory>

#include "IHittable.h"
#include "Material.h"

class Sphere : public IHittable
{
public:
	Sphere() = default;
	~Sphere() = default;

	Sphere(Vector3 _center, float _radius, std::shared_ptr<Material> _material);

	virtual bool Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const;

private:
	Vector3 center;
	float radius;
	std::shared_ptr<Material> material;
};

#endif //__SPHERE_H_INCLUDED__