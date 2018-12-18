#pragma once
#include "base.h"
class Camera
{
public:
	Camera(int id) :fNear(0.1f), fFar(1000),_id(id)
	{
		memset(at, 0, sizeof(at));
		memset(eye, 0, sizeof(eye));
		memset(up, 0, sizeof(up));
		 
	}
	
	float at[3]; 
	float eye[3];  
	float up[3];
	float fNear;
	float fFar;
	int _id; 
	float _wh_per;
	void Set(float WH_per)
	{
		float view[16];
		bx::mtxLookAt(view, eye, at,up);

		float proj[16];
		bx::mtxProj(proj, 60.0f, WH_per, fNear, fFar, bgfx::getCaps()->homogeneousDepth);
		_wh_per = WH_per;
		bgfx::setViewTransform(_id, view, proj);
	}

	//edit camera code start
	void onMousePress()
	{
		
	}

	void onMouseUp()
	{

	}

	void onMouseMove(Vector3R DertaPos)
	{
		eye[0] += DertaPos[0] / 100;
		eye[1] += DertaPos[1] / 100;
		eye[2] += DertaPos[2] / 100;
		Set(_wh_per);
	}

	//edit camera code end

};
