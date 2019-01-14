#include "../include.h"
#include "../render/Camera.h"
#include "EventSystem.h"
#include "CameraEdit.h"
#include <iostream>
using namespace std;
void CameraEdit::onDrag(Vector2R dPos)
{
	if (_pCamera == NULL)
		return ;
	/*Vector3R eulers_x(0, 0, 0);
	Vector3R eulers_y(0, 0, 0);
	Vector3R eulers_z(0, 0, 0);
	_pCamera->space.XYZ(eulers_x, eulers_y, eulers_z);
	_pCamera->selfSpaceRotate(eulers_y * (dPos.x) * -0.01);
	cout << "x=" << dPos.x << "y=" << dPos.y << endl;
	_pCamera->selfSpaceRotate(eulers_x * (dPos.y) * -0.01);*/

	Vector3R eulers_x(1, 0, 0);
	Vector3R eulers_y(0, 1, 0);
	_pCamera->selfSpaceRotate(eulers_y*dPos.x*0.03*xia_math::Deg2Rad);
	_pCamera->selfSpaceRotate(eulers_x*dPos.y*0.03*xia_math::Deg2Rad);
}

void CameraEdit::onWheelChange(int value)
{
	Vector3R eulers_z(0, 0, 0);
	_pCamera->space.Z( eulers_z);
	cout << "z=" << value << endl;
	_pCamera->space.m_postion += eulers_z * value;
}
