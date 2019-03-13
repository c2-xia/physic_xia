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
	real* getPtr() { return &m_data[0][0]; };
	const real* getPtr() const { return &m_data[0][0]; };
};


void fromToRotation(const real* from, const real* to, real mtx[3][3]);

void fromToRotation(const real* from, const real* to, real* mtx);

void MultiplyMatrices4x4REF(const Matrix4x4R& __restrict lhs, const Matrix4x4R& __restrict rhs, Matrix4x4R& __restrict res);
#endif //MATRIX_H