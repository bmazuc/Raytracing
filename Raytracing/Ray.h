#ifndef __RAY_H_INCLUDED__
#define __RAY_H_INCLUDED__

#include "Vector3.h"

struct Ray
{
	Ray() = default;
	~Ray() = default;

	Ray(Vector3 const& _origin, Vector3 const& _direction): origin(_origin), direction(_direction) {}

	Vector3 At(float t) const
	{
		return origin + direction * t;
	}

	Vector3 origin;
	Vector3 direction;
};

#endif //__RAY_H_INCLUDED__
