#ifndef VECTOR3_H
#define VECTOR3_H


template<typename T>
struct Vector3
{	 
	Vector3():x(0),y(0),z(0){}
	
	Vector3(T xx, T yy, T zz) :x(xx), y(yy), z(zz) {}
	
	T* getPtr(){ return &x;}
	
	const T* getPtr() const { return &x; }

	T operator [](unsigned char index)
	{
		if(index >=0 && index<3)
			return getPtr()[index];
		return 0;
	}

	void Set(T xx, T yy, T zz)
	{
		x = xx;
		y = yy;
		z = zz;
	}

	T len() const
	{
		T len_squal = x * x + y * y + z * z;
		T t = xia_math::xia_sqrt(len_squal);
		return t;
	}

	void normalize()
	{
		real len_squal =  x * x + y * y + z * z;
		real t = xia_math::xia_sqrt(len_squal);
		if (t != 0)
		{
			x = x / t;
			y = y / t;
			z = z / t;
		}
	}
	void operator *= (T v)
	{
		x *= v;
		y *= v;
		z *= v;
	}
	Vector3<T>& Vector3<T>::operator /= (float s)
	{ 
		x /= s;
		y /= s;
		z /= s;
		return *this;
	}
	
	static const Vector3<T>& Up()
	{
		const static Vector3<T> up_instance(0, 1, 0);
		return up_instance;
	}
	static const Vector3<T>& Zero()
	{
		const static Vector3<T> zero_instance(0,0, 0);
		return zero_instance;
	}
	

	friend static Vector3<T> operator - (Vector3<T> l, Vector3<T> r)
	{
		T x = l.x - r.x;
		T y = l.y - r.y;
		T z = l.z - r.z;

		return Vector3<T>(x,y,z);
	}
	 
	friend static Vector3<T> operator / (const Vector3<T>& inV, const real s)
	{
		Vector3<T> temp(inV);
		temp /= s;
		return temp;
	}

	friend static Vector3<T> operator * (Vector3<T> l, Vector3<T> r)
	{
		/*
		i  ,j  ,k  
		l.x,l.y,l.z
		r.x,r.y,r.z	
		*/

		T x = l.y*r.z - l.z*r.y;
		T y = l.x*r.z - l.z*r.z;
		T z = l.x*r.y - l.y*r.x;

		return Vector3<T>(x, y, z);
	}

	static  const T 		epsilon ;

	T x;
	T y;
	T z;
};



typedef Vector3<float> Vector3f;
typedef Vector3<real> Vector3R;
#endif

