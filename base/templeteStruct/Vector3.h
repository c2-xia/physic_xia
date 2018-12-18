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
	 
	T x;
	T y;
	T z;
};



typedef Vector3<float> Vector3f;
typedef Vector3<real> Vector3R;
#endif

