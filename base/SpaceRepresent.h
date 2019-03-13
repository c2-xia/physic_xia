#ifndef SPACE_REPRESENT_H
#define SPACE_REPRESENT_H

 
class SpaceRepresent
{
public:
		void initFromEye_At_Up(Vector3R eye, Vector3R at, Vector3R up);

		void toMatrix4_4(Matrix4x4R& out);

		void fromMatrix4_4(const Matrix4x4R& in);


		void rotate(QuaternionR rotate);


		void RotateAround(Vector3R axis, real euler);


		void Y(Vector3R& out);


		void X(Vector3R& out);


		void Z(Vector3R& out);

		void XYZ(Vector3R& X, Vector3R& Y, Vector3R& Z);
	 
		friend static SpaceRepresent operator * (SpaceRepresent l, SpaceRepresent r)
		{
			Matrix4x4R l_m, r_m, final_m;
			l.toMatrix4_4(l_m);
			r.toMatrix4_4(r_m);

			MultiplyMatrices4x4REF(l_m, r_m, final_m);
			SpaceRepresent result;
			result.fromMatrix4_4(final_m);
			return result;
		}
		

	//该空间在世界坐标系中的位置
	Vector3R	 m_postion;
	//该空间在世界坐标系中的旋转
	QuaternionR  m_rotatin;	
};



#endif

 