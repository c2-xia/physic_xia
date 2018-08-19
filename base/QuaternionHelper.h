
void QuaternionToMatrix(const QuaternionR& q, real* m_Data)
{ 
	// Precalculate coordinate products
	float x = q.x * 2.0F;
	float y = q.y * 2.0F;
	float z = q.z * 2.0F;
	float xx = q.x * x;
	float yy = q.y * y;
	float zz = q.z * z;
	float xy = q.x * y;
	float xz = q.x * z;
	float yz = q.y * z;
	float wx = q.w * x;
	float wy = q.w * y;
	float wz = q.w * z;

	// Calculate 3x3 matrix from orthonormal basis
	m_Data[0] = 1.0f - (yy + zz);
	m_Data[1] = xy + wz;
	m_Data[2] = xz - wy;
	m_Data[3] = 0.0F;

	m_Data[4] = xy - wz;
	m_Data[5] = 1.0f - (xx + zz);
	m_Data[6] = yz + wx;
	m_Data[7] = 0.0F;

	m_Data[8] = xz + wy;
	m_Data[9] = yz - wx;
	m_Data[10] = 1.0f - (xx + yy);
	m_Data[11] = 0.0F;

	m_Data[12] = 0.0F;
	m_Data[13] = 0.0F;
	m_Data[14] = 0.0F;
	m_Data[15] = 1.0F;
}