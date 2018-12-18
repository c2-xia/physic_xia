#ifndef PLANE_H
#define PLANE_H

#include "matrix.h"

struct Plane 
{
	Plane():_bDirty(true){}
	Vector3R _center;
	Vector3R _up;
	bool	 _bDirty;
	void matrixR(real* pMatrix)
	{
		memset( pMatrix , 0, sizeof(real) * 16);
		real temp[3][3];
		memset(temp, 0, sizeof(temp));
		fromToRotation(Vector3R::Up().getPtr(),_up.getPtr(), temp);
		
		pMatrix[0] = temp[0][0];
		pMatrix[1] = temp[0][1];
		pMatrix[2] = temp[0][2];
		pMatrix[4] = temp[1][0];
		pMatrix[5] = temp[1][1];
		pMatrix[6] = temp[1][2];
		pMatrix[8] = temp[2][0];
		pMatrix[9] = temp[2][1];
		pMatrix[10] = temp[2][2];
			 
		pMatrix[12] = _center[0];
		pMatrix[13] = _center[1];
		pMatrix[14] = _center[2];
		pMatrix[15] = 1;
	}
	void setDirty(bool bDirty) { _bDirty = bDirty; }
	bool getDirty() { return _bDirty; };
	struct IRenderAble renderData;
};


#endif
