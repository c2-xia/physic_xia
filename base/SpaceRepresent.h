#include "QuaternionHelper.h"
 
class SpaceRepresent
{
public:
	void initFromEye_At_Up(Vector3R eye, Vector3R at, Vector3R up)
	{
		m_postion = eye;

		Vector3R v_z = at - eye;
		Vector3R v_y = up;
		Vector3R v_x = v_z * v_y;
		Matrix3x3R mat;
		mat.GetW(0, 0) = v_x[0];
		mat.GetW(1, 0) = v_x[1];
		mat.GetW(2, 0) = v_x[2];

		mat.GetW(0, 1) = v_y[0];
		mat.GetW(1, 1) = v_y[1]; 
		mat.GetW(2, 1) = v_y[2];

		mat.GetW(0, 2) = v_z[0];
		mat.GetW(1, 2) = v_z[1];
		mat.GetW(2, 2) = v_z[2];
		MatrixToQuaternion(mat, m_rotatin);
	}

	void toMatrix4_4(Matrix4x4R& out)
	{
		Quaternion2Maxtrix4_4(m_rotatin,out);

		out.GetW(0, 3) = m_postion.x;
		out.GetW(1, 3) = m_postion.y;
		out.GetW(2, 3) = m_postion.z;
	}

	void rotate(QuaternionR rotate)
	{
		m_rotatin *= rotate;
	}

	void RotateAround(Vector3R axis, real euler)
	{
		axis.normalize();
		QuaternionR q(axis.x, axis.y, axis.z, euler);
		m_rotatin *= q;
	}

	void Y(Vector3R& out)
	{
		Matrix4x4R mtx;
		toMatrix4_4(mtx);
		out.x = mtx.Get(0, 1);
		out.y = mtx.Get(1, 1);
		out.z = mtx.Get(2, 1);
	}
	
	void X(Vector3R& out)
	{
		Matrix4x4R mtx;
		toMatrix4_4(mtx);
		out.x = mtx.Get(0, 0);
		out.y = mtx.Get(1, 0);
		out.z = mtx.Get(2, 0);
	}
	
	void Z(Vector3R& out)
	{
		Matrix4x4R mtx;
		toMatrix4_4(mtx);
		out.x = mtx.Get(0, 2);
		out.y = mtx.Get(1, 2);
		out.z = mtx.Get(2, 2);
	}
	void XYZ(Vector3R& X, Vector3R& Y, Vector3R& Z)
	{
		Matrix4x4R mtx;
		toMatrix4_4(mtx);
		X.x = mtx.Get(0, 0);
		X.y = mtx.Get(1, 0);
		X.z = mtx.Get(2, 0);

		Y.x = mtx.Get(0, 1);
		Y.y = mtx.Get(1, 1);
		Y.z = mtx.Get(2, 1);

		Z.x = mtx.Get(0, 2);
		Z.y = mtx.Get(1, 2);
		Z.z = mtx.Get(2, 2);
	}
private:
	//该空间在世界坐标系中的位置
	Vector3R	 m_postion;
	//该空间在世界坐标系中的旋转
	QuaternionR  m_rotatin;	
};


 