#pragma once
#include "base.h"
#include "SpaceRepresent.h"
#include "../runtime/GlobalValues.h"
#include "xia_math/xia_math.hpp"

class Camera
{
public:
	Camera(int id) :fNear(0.1f), fFar(1000),_id(id), _fov(60.0f)
	{
		
	}
	SpaceRepresent space;


	float fNear;
	float fFar;
	int _id; 
	float _wh_per;
	float _fov;
	void Set(float WH_per)
	{ 
		Matrix4x4R view;
		space.toMatrix4_4(view);
		float proj[16];
		bx::mtxProj(proj, _fov, WH_per, fNear, fFar, bgfx::getCaps()->homogeneousDepth );
		_wh_per = WH_per;
		bgfx::setViewTransform(_id, view.m_data, proj);
	}

	void selfSpaceRotate(Vector3R euler)
	{ 
		QuaternionR q = EulerToQuaternion(euler);
		space.rotate(q);
	}

	void RotateAround(Vector3R pos, Vector3R axis , real euler )
	{
		 
	}

	//edit camera code start
	void onMousePress()
	{
		
	}

	void onMouseUp()
	{

	}

	void onMouseMove(Vector3R start,Vector3R end)
	{
		unsigned int half_w = GlobalValues::instance.width / 2;
		unsigned int half_h = GlobalValues::instance.height / 2;

		float real_h_half = xia_math::xia_tan(_fov * xia_math::Deg2Rad / 2 ) * this->fNear;
		float real_w_half = _wh_per * real_h_half;
		float p_x_start = start.x / half_w * real_w_half;
		float p_y_start = start.y / half_h * real_h_half;

		float p_x_end = end.x / half_w * real_w_half;
		float p_y_end = end.y / half_h * real_h_half;

		 

		if (p_x_start != p_x_end || p_y_start != p_y_end)
		{
			Vector3R a(p_x_start, p_y_start, this->fNear);
			Vector3R b(p_x_end  , p_y_end  , this->fNear);
			/*Vector3R a(0, 0,1);
			Vector3R b(0.01,0.01, 1);*/
			QuaternionR q = FromToQuaternionSafe(a, b);
			/*Vector3R a(0.01f, 0, 0);
			QuaternionR q = EulerToQuaternion(a);*/

			space.rotate(q);
		}
		
	}

	//edit camera code end

};
