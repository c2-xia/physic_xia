#ifndef SPACE_REPRESENT_H
#define SPACE_REPRESENT_H

 
class SpaceRepresent
{
public:
		void initFromEye_At_Up(Vector3R eye, Vector3R at, Vector3R up);

		void toMatrix4_4(Matrix4x4R& out);


		void rotate(QuaternionR rotate);


		void RotateAround(Vector3R axis, real euler);


		void Y(Vector3R& out);


		void X(Vector3R& out);


		void Z(Vector3R& out);

		void XYZ(Vector3R& X, Vector3R& Y, Vector3R& Z);
	 

	//该空间在世界坐标系中的位置
	Vector3R	 m_postion;
	//该空间在世界坐标系中的旋转
	QuaternionR  m_rotatin;	
};

#endif

 