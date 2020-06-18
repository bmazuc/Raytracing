#ifndef __VEC3_H_INCLUDED__
#define  __VEC3_H_INCLUDED__

#include <cmath>

struct Vector3
{
	Vector3() = default;
	~Vector3() = default;

	Vector3(float x, float y, float z) : values{x, y, z} {}

	float x() const { return values[0]; }
	float y() const { return values[1]; }
	float z() const { return values[2]; }
	float r() const { return values[0]; }
	float g() const { return values[1]; }
	float b() const { return values[2]; }

	Vector3 operator-() const { return Vector3(-values[0], -values[1], -values[2]); }
	float operator[](int i) const { return values[i]; }
	float& operator[](int i) { return values[i]; }

	Vector3 operator+(Vector3 const& rhs) const
	{
		return Vector3(values[0] + rhs.values[0], values[1] + rhs.values[1], values[2] + rhs.values[2]);
	}

	Vector3& operator+=(Vector3 const& rhs)
	{
		values[0] += rhs.values[0];
		values[1] += rhs.values[1];
		values[2] += rhs.values[2];
		return *this;
	}

	Vector3 operator-(Vector3 const& rhs) const
	{
		return Vector3(values[0] - rhs.values[0], values[1] - rhs.values[1], values[2] - rhs.values[2]);
	}

	Vector3& operator-=(Vector3 const& rhs)
	{
		values[0] -= rhs.values[0];
		values[1] -= rhs.values[1];
		values[2] -= rhs.values[2];
		return *this;
	}

	// Component-wise multiplication
	Vector3 operator*(Vector3 const& rhs) const
	{
		return Vector3(values[0] * rhs.values[0], values[1] * rhs.values[1], values[2] * rhs.values[2]);
	}

	Vector3& operator*=(Vector3 const& rhs)
	{
		values[0] *= rhs.values[0];
		values[1] *= rhs.values[1];
		values[2] *= rhs.values[2];
		return *this;
	}

	Vector3 operator*(float t) const
	{
		return Vector3(values[0] * t, values[1] * t, values[2] * t);
	}

	Vector3& operator*=(float const t)
	{
		values[0] *= t;
		values[1] *= t;
		values[2] *= t;
		return *this;
	}

	Vector3 operator/(Vector3 const& rhs) const
	{
		return Vector3(values[0] / rhs.values[0], values[1] / rhs.values[1], values[2] / rhs.values[2]);
	}

	Vector3& operator/=(Vector3 const& rhs)
	{
		values[0] /= rhs.values[0];
		values[1] /= rhs.values[1];
		values[2] /= rhs.values[2];
		return *this;
	}

	Vector3 operator/(float t) const
	{
		return Vector3(values[0] / t, values[1] / t, values[2] / t);
	}

	Vector3& operator/=(float const t)
	{
		values[0] /= t;
		values[1] /= t;
		values[2] /= t;
		return *this;
	}

	static float DotProduct(Vector3 const& vector1, Vector3 const& vector2)
	{
		return vector1.values[0] * vector2.values[0] + vector1.values[1] * vector2.values[1] + vector1.values[2] * vector2.values[2];
	}

	static Vector3 CrossProduct(Vector3 const& vector1, Vector3 const& vector2)
	{
		return Vector3(vector1.values[1] * vector2.values[2] - vector1.values[2] * vector2.values[1],
			vector1.values[2] * vector2.values[0] - vector1.values[0] * vector2.values[2],
			vector1.values[0] * vector2.values[1] - vector1.values[1] * vector2.values[0]);
	}

	float Length() const { return std::sqrt(LengthSqr()); }

	float LengthSqr() const { return values[0] * values[0] + values[1] * values[1] + values[2] * values[2]; }

	void Normalize()
	{
		float length = Length();
		values[0] /= length;
		values[1] /= length;
		values[2] /= length;
	}

	Vector3 Normalized() const
	{
		Vector3 res = *this;
		res.Normalize();
		return res;
	}

	static Vector3 Reflect(Vector3 const& direction, Vector3 const& normal)
	{
		return direction - normal * DotProduct(direction, normal) * 2.f;
	}

	static Vector3 Refract(Vector3 const& incident, Vector3 const& normal, float refractionIndiceRatio)
	{
		float cosTheta = fmin(DotProduct(-incident, normal), 1.f);
		Vector3 refractedRayParallel = (incident + normal * cosTheta) * refractionIndiceRatio;
		Vector3 refractedRayPerp = normal * -std::sqrt(1.f - refractedRayParallel.LengthSqr());
		return refractedRayParallel + refractedRayPerp;
	}
	
	float values[3];
};

/*inline std::istream& operator>>(std::istream& stream, Vector3& vector)
{
	stream >> vector.values[0] >> vector.values[1] >> vector.values[2];
	return stream;
}

inline std::ostream& operator<<(std::ostream& stream, Vector3 const& vector)
{
	stream << vector.values[0] << " " << vector.values[1] << " " << vector.values[2];
	return stream;
}*/

#endif //__VEC3_H_INCLUDED__
