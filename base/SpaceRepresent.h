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

	void RotateAround(Vector3R dic, real value)
	{

	}
private:
	//该空间在世界坐标系中的位置
	Vector3R	 m_postion;
	//该空间在世界坐标系中的旋转
	QuaternionR  m_rotatin;	
};


 