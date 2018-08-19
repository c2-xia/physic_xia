#ifndef PLANE_H
#define PLANE_H
 

struct Plane 
{
	Vector3R _center;
	Vector3R _up;

	void matrixR(real* pMatrix)
	{

		QuaternionToMatrix(q, pMatrix);
		pMatrix[12] = pos[0];
		pMatrix[13] = pos[1];
		pMatrix[14] = pos[2];
	}
};


#endif
