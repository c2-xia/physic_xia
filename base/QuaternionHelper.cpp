#include "stdafx.h"
#include "base.h"
#include "templeteStruct/templeteInclude.h"
#include "matrix.h"
#include "xia_math/xia_math.hpp"
#include "QuaternionHelper.h"


void MatrixToQuaternion(const Matrix3x3R& kRot, QuaternionR& q)
{
	real Trace = kRot.Get(0, 0) + kRot.Get (1, 1) + kRot.Get (2, 2);
	real fRoot;

	if (Trace > 0.0f)
	{
		fRoot = sqrt(Trace + 1.0f);  // 2w
		q.w = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;  // 1/(4w)
		q.x = (kRot.Get(2, 1) - kRot.Get(1, 2))*fRoot;
		q.y = (kRot.Get(0, 2) - kRot.Get(2, 0))*fRoot;
		q.z = (kRot.Get(1, 0) - kRot.Get(0, 1))*fRoot;
	}
	else
	{
		// |w| <= 1/2
		int s_iNext[3] = { 1, 2, 0 };
		int i = 0;
		if (kRot.Get(1, 1) > kRot.Get(0, 0))
			i = 1;
		if (kRot.Get(2, 2) > kRot.Get(i, i))
			i = 2;
		int j = s_iNext[i];
		int k = s_iNext[j];

		fRoot = sqrt(kRot.Get(i, i) - kRot.Get(j, j) - kRot.Get(k, k) + 1.0f);
		float* apkQuat[3] = { &q.x, &q.y, &q.z };
		//AssertIf(fRoot < 0.00001F);
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f / fRoot;
		q.w = (kRot.Get(k, j) - kRot.Get(j, k)) * fRoot;
		*apkQuat[j] = (kRot.Get(j, i) + kRot.Get(i, j))*fRoot;
		*apkQuat[k] = (kRot.Get(k, i) + kRot.Get(i, k))*fRoot;
	}
	//q = Normalize(q);
}


void Quaternion2Maxtrix4_4(const QuaternionR& q, Matrix4x4R& m)
{ 
	float x = q.x * 2.0F;
	float y = q.y * 2.0F;
	float z = q.z * 2.0F;
	float xx = q.x * x;
	float yy = q.y * y;
	float zz = q.z * z;
	float xy = q.x * y;
	float xz = q.x * z;
	float yz = q.y * z;
	float wx = q.w * x;
	float wy = q.w * y;
	float wz = q.w * z;

	// Calculate 3x3 matrix from orthonormal basis
	m.m_data[0][0] = 1.0f - (yy + zz);
	m.m_data[1][0] = xy + wz;
	m.m_data[2][0] = xz - wy;
	m.m_data[3][0] = 0.0F;

	m.m_data[0][1] = xy - wz;
	m.m_data[1][1] = 1.0f - (xx + zz);
	m.m_data[2][1] = yz + wx;
	m.m_data[3][1] = 0.0F;

	m.m_data[0][2] = xz + wy;
	m.m_data[1][2] = yz - wx;
	m.m_data[2][2] = 1.0f - (xx + yy);
	m.m_data[3][2] = 0.0F;

	m.m_data[0][3] = 0.0F;
	m.m_data[1][3] = 0.0F;
	m.m_data[2][3] = 0.0F;
	m.m_data[3][3] = 1.0F;
}


QuaternionR EulerToQuaternion(const Vector3R& someEulerAngles)
{
	float cX(cos(someEulerAngles.x / 2.0f));
	float sX(sin(someEulerAngles.x / 2.0f));

	float cY(cos(someEulerAngles.y / 2.0f));
	float sY(sin(someEulerAngles.y / 2.0f));

	float cZ(cos(someEulerAngles.z / 2.0f));
	float sZ(sin(someEulerAngles.z / 2.0f));

	QuaternionR qX(sX, 0.0F, 0.0F, cX);
	QuaternionR qY(0.0F, sY, 0.0F, cY);
	QuaternionR qZ(0.0F, 0.0F, sZ, cZ);

	QuaternionR q = (qY * qX) * qZ;
	 
	return q;
}

QuaternionR FromToQuaternionSafe(const Vector3R& lhs, const Vector3R& rhs)
{
	real lhsMag = lhs.len();
	real rhsMag = rhs.len();
	if (lhsMag < Vector3R::epsilon || rhsMag < Vector3R::epsilon)
		return QuaternionR::identity();
	else
		return FromToQuaternion(lhs / lhsMag, rhs / rhsMag);
}

QuaternionR FromToQuaternion(const Vector3R& from, const Vector3R& to)
{
	Matrix3x3R m;
	fromToRotation(from.getPtr(),to.getPtr(), m.m_data);
	QuaternionR q;
	MatrixToQuaternion(m, q);
	return q;
}