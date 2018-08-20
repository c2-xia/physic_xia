#ifndef PLANE_H
#define PLANE_H

#include "matrix.h"

struct Plane 
{
	Vector3R _center;
	Vector3R _up;

	void matrixR(real* pMatrix)
	{
		
		fromToRotation(Vector3R::Up().getPtr(),_up.getPtr(), pMatrix);
		pMatrix[12] = _center[0];
		pMatrix[13] = _center[1];
		pMatrix[14] = _center[2];
	}
};


#endif
