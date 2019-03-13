#ifndef CAMERA_H
#define CAMERA_H

#include "base.h"
#include "SpaceRepresent.h"


class Camera
{
public:
	Camera(int id) :fNear(0.01f), fFar(1000), _id(id), _fov(60.0f)
	{

	}
	void Set(float WH_per);
	void selfSpaceRotate(Vector3R euler);
	void RotateAround(Vector3R pos, Vector3R axis, real euler);


	SpaceRepresent space;

	float fNear;
	float fFar;
	int _id;
	float _wh_per;
	float _fov;
};


#endif // !CAMERA_H
