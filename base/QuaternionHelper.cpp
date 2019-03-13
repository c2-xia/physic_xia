#include "stdafx.h"
#include "base.h"
#include "templeteStruct/templeteInclude.h"
#include "matrix.h"
#include "xia_math/xia_math.hpp"
#include "QuaternionHelper.h"


#ifndef kPI
#define kPI 3.14159265358979323846264338327950288419716939937510F
#endif

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


void MatrixToQuaternion(const Matrix4x4R& kRot, QuaternionR& q)
{
	real Trace = kRot.Get(0, 0) + kRot.Get(1, 1) + kRot.Get(2, 2);
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

void Quaternion2Maxtrix3_3(const QuaternionR& q, Matrix3x3R& m)
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
 

	m.m_data[0][1] = xy - wz;
	m.m_data[1][1] = 1.0f - (xx + zz);
	m.m_data[2][1] = yz + wx;
 

	m.m_data[0][2] = xz + wy;
	m.m_data[1][2] = yz - wx;
	m.m_data[2][2] = 1.0f - (xx + yy);
 
}


inline void MakePositive(Vector3R& euler)
{
	const float negativeFlip = -0.0001F;
	const float positiveFlip = (kPI * 2.0F) - 0.0001F;

	if (euler.x < negativeFlip)
		euler.x += 2.0 * kPI;
	else if (euler.x > positiveFlip)
		euler.x -= 2.0 * kPI;

	if (euler.y < negativeFlip)
		euler.y += 2.0 * kPI;
	else if (euler.y > positiveFlip)
		euler.y -= 2.0 * kPI;

	if (euler.z < negativeFlip)
		euler.z += 2.0 * kPI;
	else if (euler.z > positiveFlip)
		euler.z -= 2.0 * kPI;
}

/// This is YXZ euler conversion
bool MatrixToEuler(const Matrix3x3R& matrix, Vector3R& v)
{
	// from http://www.geometrictools.com/Documentation/EulerAngles.pdf
	// YXZ order
	if (matrix.Get(1, 2) < 0.999F) // some fudge for imprecision
	{
		if (matrix.Get(1, 2) > -0.999F) // some fudge for imprecision
		{
			v.x = asin(-matrix.Get(1, 2));
			v.y = atan2(matrix.Get(0, 2), matrix.Get(2, 2));
			v.z = atan2(matrix.Get(1, 0), matrix.Get(1, 1));
			MakePositive(v);
			return true;
		}
		else
		{
			// WARNING.  Not unique.  YA - ZA = atan2(r01,r00)
			v.x = kPI * 0.5F;
			v.y = atan2(matrix.Get(0, 1), matrix.Get(0, 0));
			v.z = 0.0F;
			MakePositive(v);

			return false;
		}
	}
	else
	{
		// WARNING.  Not unique.  YA + ZA = atan2(-r01,r00)
		v.x = -kPI * 0.5F;
		v.y = atan2(-matrix.Get(0, 1), matrix.Get(0, 0));
		v.z = 0.0F;
		MakePositive(v);
		return false;
	}
}

Vector3R QuaternionToEuler(const QuaternionR& quat)
{
	Matrix3x3R m;
	Vector3f rot;
	Quaternion2Maxtrix3_3(quat, m);
	MatrixToEuler(m, rot);
	return rot;
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