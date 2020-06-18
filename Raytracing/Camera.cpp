#include "pch.h"
#include "Camera.h"
#include "MathUtility.h"

Camera::Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 viewUp, float vfov, float aspectRatio, float aperture, float focusDistance)
{
	float theta = degreesToRadians(vfov);
	float h = tan(theta / 2.f);
	float viewportHeight = 2.0f * h;
	float viewportWidth = aspectRatio * viewportHeight;

	forward = (lookFrom - lookAt).Normalized();
	right = Vector3::CrossProduct(viewUp, forward).Normalized();
	up = Vector3::CrossProduct(forward, right);

	origin = lookFrom;
	horizontal = right * viewportWidth * focusDistance;
	vertical = up * viewportHeight * focusDistance;
	lowerLeftCorner = origin - (horizontal / 2) - (vertical / 2) - forward * focusDistance;

	lensRadius = aperture / 2.f;
}


Ray Camera::PointToRay(float x, float y)
{
	Vector3 random = RandomInUnitDisk() * lensRadius;
	Vector3 offset = right * random.x() + up * random.y();
	return Ray(origin + offset, lowerLeftCorner + (horizontal * x) + (vertical * y) - origin - offset);
}
