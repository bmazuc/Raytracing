#ifndef __HITTABLE_LIST_H_INCLUDED__
#define __HITTABLE_LIST_H_INCLUDED__

#include <memory>
#include <vector>

#include "IHittable.h"

class HittableList : public IHittable
{
public:
	HittableList() = default;
	~HittableList() = default;

	void Add(std::shared_ptr<IHittable> object) { objects.push_back(object); }
	void Clear() { objects.clear(); }

	virtual bool Hit(Ray const& r, float tMin, float tMax, RayHitInfo& info) const;

private:
	std::vector<std::shared_ptr<IHittable>> objects;
};

#endif //__HITTABLE_LIST_H_INCLUDED__