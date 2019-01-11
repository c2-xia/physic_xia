#ifndef MATRIX_H
#define MATRIX_H


class  Matrix3x3R
{
public:
	real m_data[3][3];
	const real& Get(int row, int column) const { return m_data[row][column]; }
	real& GetW(int row, int column)  { return m_data[row][column]; }
};

class  Matrix4x4R
{
public:
	real m_data[4][4];
	const real& Get(int row, int column) const { return m_data[row][column]; }
	real& GetW(int row, int column) { return m_data[row][column]; }
};


void fromToRotation(const real* from, const real* to, real mtx[3][3]);

void fromToRotation(const real* from, const real* to, real* mtx);
#endif //MATRIX_H