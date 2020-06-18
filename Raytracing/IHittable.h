#ifndef __I_HITTABLE_H_INCLUDED__
#define __I_HITTABLE_H_INCLUDED__

#include "Ray.h"
#include "RayHitInfo.h"

class IHittable
{
	public:
		virtual bool Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const = 0;
};


#endif //__I_HITTABLE_H_INCLUDED__