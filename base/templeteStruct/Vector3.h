#ifndef VECTOR3_H
#define VECTOR3_H

template<typename T>
struct Vector3
{
	T x;
	T y;
	T z;
	T* getPtr(){ return &x;}
	T operator [](unsigned char index)
	{
		if(index >=0&& index<3)
			return getPtr()[index];
		return 0;
	}
};

typedef Vector3<float> Vector3f;

#endif

