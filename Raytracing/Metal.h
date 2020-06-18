#ifndef __METAL_H_INCLUDED__
#define __METAL_H_INCLUDED__

#include "Material.h"

class Metal : public Material
{
public:
	Metal() = delete;
	Metal(Vector3 const& _albedo, float _fuziness);
	~Metal() = default;

	virtual bool Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const;

private:
	Vector3 albedo;
	float fuzziness;
};

#endif //__METAL_H_INCLUDED__