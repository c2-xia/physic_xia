
void MatrixToQuaternion(const Matrix3x3R& kRot, QuaternionR& q);

void Quaternion2Maxtrix4_4(const QuaternionR& q, Matrix4x4R& m);

QuaternionR EulerToQuaternion(const Vector3R& someEulerAngles);

QuaternionR FromToQuaternionSafe(const Vector3R& lhs, const Vector3R& rhs);

QuaternionR FromToQuaternion(const Vector3R& from, const Vector3R& to);