#ifndef __RAY_HIT_INFO_H_INCLUDED__
#define __RAY_HIT_INFO_H_INCLUDED__

#include "Vector3.h"
#include <memory>
class Material;

struct RayHitInfo
{
	Vector3 point;
	Vector3 normal;
	std::shared_ptr<Material> material;
	float t;
	bool isFrontFace;
};

#endif //__RAY_HIT_INFO_H_INCLUDED__