#ifndef __CAMERA_H_INCLUDED__
#define __CAMERA_H_INCLUDED__

#include "Ray.h"

class Camera
{
public:
	Camera() = delete;
	Camera(Vector3 lookFrom, Vector3 lookAt, Vector3 viewUp, float vfov, float aspectRatio, float aperture, float focusDistance, float _shutterOpenTime, float _shutterCloseTime);
	~Camera() = default;

	Ray PointToRay(float x, float y);

private:
	Vector3 origin;
	Vector3 lowerLeftCorner;
	Vector3 horizontal;
	Vector3 vertical;

	Vector3 forward;
	Vector3 right;
	Vector3 up;

	float lensRadius;

	float shutterOpenTime;
	float shutterCloseTime;
};

#endif // __CAMERA_H_INCLUDED__