#include "common.h"
#include "bgfx_utils.h"
#include "../base/base.h"
#include "../base/xia_math/xia_math.hpp"
#include "../base/templeteStruct/templeteInclude.h"
#include "../base/matrix.h"
#include "../base/QuaternionHelper.h"
#include "../runtime/GlobalValues.h"

#include "Camera.h"


void Camera::Set(float WH_per)
{
	Matrix4x4R view;
	space.toMatrix4_4(view);
	float proj[16];

	bx::mtxProj(proj, _fov, WH_per, fNear, fFar, bgfx::getCaps()->homogeneousDepth);
	_wh_per = WH_per;
	bgfx::setViewTransform(_id, view.m_data, proj);
}

void Camera::selfSpaceRotate(Vector3R euler)
{
	QuaternionR q = EulerToQuaternion(euler);
	space.rotate(q);
}

void Camera::RotateAround(Vector3R pos, Vector3R axis, real euler)
{

}