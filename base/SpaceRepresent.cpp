#include "../include.h"
#include "base.h"
#include "matrix.h"

#include "QuaternionHelper.h"
#include "SpaceRepresent.h"
 

void SpaceRepresent::initFromEye_At_Up(Vector3R eye, Vector3R at, Vector3R up)
{
	m_postion = eye;

	Vector3R v_z = at - eye;
	Vector3R v_y = up;
	Vector3R v_x = v_y * v_z ;
	v_x.normalize();
	v_y.normalize();
	v_z.normalize();

	Matrix3x3R mat;
	mat.GetW(0, 0) = v_x[0];
	mat.GetW(1, 0) = v_x[1];
	mat.GetW(2, 0) = v_x[2];

	mat.GetW(0, 1) = v_y[0];
	mat.GetW(1, 1) = v_y[1]; 
	mat.GetW(2, 1) = v_y[2];

	mat.GetW(0, 2) = v_z[0];
	mat.GetW(1, 2) = v_z[1];
	mat.GetW(2, 2) = v_z[2];
	MatrixToQuaternion(mat, m_rotatin);
	Matrix4x4R test;
	toMatrix4_4(test);

	float view[16];
	bx::mtxLookAt(view, eye.getPtr(), at.getPtr(),up.getPtr());

	int i = 0;
}

void SpaceRepresent::toMatrix4_4(Matrix4x4R& out)
{
	Quaternion2Maxtrix4_4(m_rotatin,out);
	Vector3R x_axis(out.Get(0, 0), out.Get(1, 0), out.Get(2, 0));
	Vector3R y_axis(out.Get(0, 1), out.Get(1, 1), out.Get(2, 1));
	Vector3R z_axis(out.Get(0, 2), out.Get(1, 2), out.Get(2, 2));
 
	out.GetW(3, 0) = -Dot(m_postion, x_axis);
	out.GetW(3, 1) = -Dot(m_postion, y_axis);
	out.GetW(3, 2) = -Dot(m_postion, z_axis);
	out.GetW(3, 3) = 1;
}

void SpaceRepresent::rotate(QuaternionR rotate)
{
	m_rotatin *= rotate;
}

void SpaceRepresent::RotateAround(Vector3R axis, real euler)
{
	axis.normalize();
	QuaternionR q(axis.x, axis.y, axis.z, euler);
	m_rotatin *= q;
}

void SpaceRepresent::Y(Vector3R& out)
{
	Matrix4x4R mtx;
	toMatrix4_4(mtx);
	out.x = mtx.Get(0, 1);
	out.y = mtx.Get(1, 1);
	out.z = mtx.Get(2, 1);
}
	
void SpaceRepresent::X(Vector3R& out)
{
	Matrix4x4R mtx;
	toMatrix4_4(mtx);
	out.x = mtx.Get(0, 0);
	out.y = mtx.Get(1, 0);
	out.z = mtx.Get(2, 0);
}
	
void SpaceRepresent::Z(Vector3R& out)
{
	Matrix4x4R mtx;
	toMatrix4_4(mtx);
	out.x = mtx.Get(0, 2);
	out.y = mtx.Get(1, 2);
	out.z = mtx.Get(2, 2);
}
void SpaceRepresent::XYZ(Vector3R& X, Vector3R& Y, Vector3R& Z)
{
	Matrix4x4R mtx;
	toMatrix4_4(mtx);
	X.x = mtx.Get(0, 0);
	X.y = mtx.Get(1, 0);
	X.z = mtx.Get(2, 0);

	Y.x = mtx.Get(0, 1);
	Y.y = mtx.Get(1, 1);
	Y.z = mtx.Get(2, 1);

	Z.x = mtx.Get(0, 2);
	Z.y = mtx.Get(1, 2);
	Z.z = mtx.Get(2, 2);
}
 

 