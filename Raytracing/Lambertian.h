#ifndef __LAMBERTIAN_H_INCLUDED__
#define __LAMBERTIAN_H_INCLUDED__

#include "Material.h"

class Lambertian : public Material
{
public:
	Lambertian() = delete;
	Lambertian(Vector3 const& _albedo);
	~Lambertian() = default;

	virtual bool Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const;

private:
	Vector3 albedo;
};

#endif //__LAMBERTIAN_H_INCLUDED__