#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

#include "Ray.h"
#include "RayHitInfo.h"

class Material
{
public:
	virtual bool Scatter(Ray const& rayIn, RayHitInfo const& info, Vector3& attenuation, Ray& scattered) const = 0;
};

#endif //__MATERIAL_H_INCLUDED__
