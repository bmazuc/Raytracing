#ifndef __DIELECTRIC_H_INCLUDED__
#define __DIELECTRIC_H_INCLUDED__

#include "Material.h"

class Dielectric : public Material
{
public:
	Dielectric() = delete;
	Dielectric(float _refractionIndex);
	~Dielectric() = default;

	virtual bool Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const;

private:
	float refractionIndex;
};

#endif //__DIELECTRIC_H_INCLUDED__