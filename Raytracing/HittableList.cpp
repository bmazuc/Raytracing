#include "pch.h"
#include "HittableList.h"


bool HittableList::Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const
{
	RayHitInfo tempInfo;
	bool hasHitAnything = false;
	float closest = tMax;
	int size = objects.size();

	for (int i = 0; i < size; ++i)
	{
		if (objects[i]->Hit(r, tMin, closest, tempInfo))
		{
			hasHitAnything = true;
			closest = tempInfo.t;
			info = tempInfo;
		}
	}

	return hasHitAnything;
}
