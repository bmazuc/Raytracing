#ifndef __MOVING_SPHERE_H_INCLUDED__
#define __MOVING_SPHERE_H_INCLUDED__

#include "IHittable.h"
#include "Material.h"

class MovingSphere : public IHittable
{
public:
	MovingSphere() = default;
	~MovingSphere() = default;

	MovingSphere(Vector3 _center0, Vector3 _center1, float t0, float t1, float _radius, std::shared_ptr<Material> _material);

	virtual bool Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const;

	Vector3 GetCenter(float time) const;

private:
	Vector3 center0, center1;
	float time0, time1;
	float radius;
	std::shared_ptr<Material> material;
};

#endif //__MOVING_SPHERE_H_INCLUDED__