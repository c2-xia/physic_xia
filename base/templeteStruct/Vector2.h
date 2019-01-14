#ifndef VECTOR2_H
#define VECTOR2_H

template<typename T>
struct Vector2
{
	T x;
	T y;
	T* getPtr(){ return &x;}
	T operator [](unsigned char index)
	{
		if(index >=0&& index<2)
			return getPtr()[index];
		return 0;
	}	 
};

typedef Vector2<float> Vector2f;
typedef Vector2<real> Vector2R;
#endif

