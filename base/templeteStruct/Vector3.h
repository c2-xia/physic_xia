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
	static const Vector3& Up()
	{
		const Vector3 up_instance(0, 1, 0);
		return up_instance;
	}

	T x;
	T y;
	T z;
};

typedef Vector3<float> Vector3f;
typedef Vector3<real> Vector3R;
#endif

