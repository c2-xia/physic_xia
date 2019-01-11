#ifndef QUATERNION_H
#define QUATERNION_H

class QuaternionR
{
public:

	QuaternionR():x(0), y(0), z(0), w(1)
	{

	}

	QuaternionR(real xx,real yy,real zz,real ww) :x(xx), y(yy), z(zz), w(ww)
	{

	}

	inline QuaternionR&	operator /= (const real aScalar)
	{
		x /= aScalar;
		y /= aScalar;
		z /= aScalar;
		w /= aScalar;
		return *this;
	}

	inline QuaternionR& operator+= (const QuaternionR& aQuat)
	{
		x += aQuat.x;
		y += aQuat.y;
		z += aQuat.z;
		w += aQuat.w;
		return *this;
	}

	inline QuaternionR& operator-= (const QuaternionR& aQuat)
	{
		x -= aQuat.x;
		y -= aQuat.y;
		z -= aQuat.z;
		w -= aQuat.w;
		return *this;
	}

	inline QuaternionR&  operator *= (real aScalar)
	{
		x *= aScalar;
		y *= aScalar;
		z *= aScalar;
		w *= aScalar;
		return *this;
	}
	inline QuaternionR&	QuaternionR::operator *= (const QuaternionR& 	rhs)
	{
		real tempx = w * rhs.x + x * rhs.w + y * rhs.z - z * rhs.y;
		real tempy = w * rhs.y + y * rhs.w + z * rhs.x - x * rhs.z;
		real tempz = w * rhs.z + z * rhs.w + x * rhs.y - y * rhs.x;
		real tempw = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
		x = tempx; y = tempy; z = tempz; w = tempw;
		return *this;
	}
	static  inline real SqrtImpl(real f)
	{ 
		return sqrt(f); 
	}

	static inline real Dot(const QuaternionR& q1, const QuaternionR& q2)
	{
		return (q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w);
	}

	static  inline real SqrMagnitude(const QuaternionR& q)
	{
		return Dot(q, q);
	}

	static inline real Magnitude(const QuaternionR& q)
	{
		return SqrtImpl(SqrMagnitude(q));
	}
	real  x, y, z, w;
	friend QuaternionR Normalize(const QuaternionR& q) { return q / Magnitude(q); }
	friend QuaternionR	operator / (const QuaternionR& q, const real s)
	{
		QuaternionR t(q);
		return t /= s;
	}
	inline friend QuaternionR operator * (const QuaternionR& lhs, const QuaternionR& rhs)
	{
		return QuaternionR(
			lhs.w*rhs.x + lhs.x*rhs.w + lhs.y*rhs.z - lhs.z*rhs.y,
			lhs.w*rhs.y + lhs.y*rhs.w + lhs.z*rhs.x - lhs.x*rhs.z,
			lhs.w*rhs.z + lhs.z*rhs.w + lhs.x*rhs.y - lhs.y*rhs.x,
			lhs.w*rhs.w - lhs.x*rhs.x - lhs.y*rhs.y - lhs.z*rhs.z);
	}

	static QuaternionR identity() { return QuaternionR(0.0, 0.0, 0.0, 1.0); }
};

#endif