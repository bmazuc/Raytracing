#ifndef __MATH_UTILITY_H_INCLUDED__
#define __MATH_UTILITY_H_INCLUDED__

#include "Vector3.h"
#include <limits>

float const infinity = std::numeric_limits<float>::infinity();
float const pi = 3.1415926535897932385;

inline float degreesToRadians(float degrees) { return degrees * pi / 180.f; }

inline float radiansToDegrees(float radians) { return radians * 180.f / pi; }

// Returns a random real in [0,1)
inline float randomFloat(){ return rand() / (RAND_MAX + 1.0); }

// Returns a random real in [min,max)
inline double randomFloat(float min, float max) { return min + (max - min) * randomFloat(); }

inline Vector3 randomVector3() { return Vector3(randomFloat(), randomFloat(), randomFloat()); }

inline Vector3 randomVector3(float min, float max) { return Vector3(randomFloat(min, max), randomFloat(min, max), randomFloat(min, max)); }

inline Vector3 RandomUnitVector()
{
	float a = randomFloat(0.f, 2.f * pi);
	float z = randomFloat(-1.f, 1.f);
	float r = std::sqrt(1.f - z * z);
	return Vector3(r*cos(a), r*sin(a), z);
}

inline Vector3 RandomInUnitSphere()
{
	while (true)
	{
		Vector3 point = randomVector3(-1.f, 1.f);
		if (point.LengthSqr() >= 1) continue;
		return point;
	}
}

inline Vector3 RandomInHemisphere(Vector3 const& normal) 
{
	Vector3 inUnitSphere = RandomInUnitSphere();
	if (Vector3::DotProduct(inUnitSphere, normal) > 0.f) // In the same hemisphere as the normal
		return inUnitSphere;
	else
		return -inUnitSphere;
}

inline Vector3 RandomInUnitDisk()
{
	while (true)
	{
		while (true)
		{
			Vector3 point = Vector3(randomFloat(-1.f, 1.f), randomFloat(-1.f, 1.f), 0.f);
			if (point.LengthSqr() >= 1.f) continue;
			return point;
		}
	}
}

inline float Clamp(float x, float min, float max)
{
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

inline float Clamp01(float x)
{
	return Clamp(x, 0.f, 1.f);
}

inline float Schlick(float cosine, float refractionIndex)
{
	float r0 = (1 - refractionIndex) / (1 + refractionIndex);
	r0 *= r0;
	return r0 + (1 - r0) * pow(1 - cosine, 5);
}

#endif //__MATH_UTILITY_H_INCLUDED__