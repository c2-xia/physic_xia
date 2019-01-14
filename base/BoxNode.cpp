#include "base.h"
#include "xia_math/xia_math.hpp"
#include "matrix.h"
#include "templeteStruct/templeteInclude.h"
#include "QuaternionHelper.h"
#include "SpaceRepresent.h"
#include "../render/NodeRender.h"

#include "BoxNode.h"

void BOX_NODE::set(Vector3R bottom,unsigned char nDirection)
{
	if (nDirection >= 0 && nDirection < 3)
	{
		_space.m_postion = bottom;
		_space.m_postion.getPtr()[nDirection] += _scale[nDirection];
	}
}

void BOX_NODE::matrixR(Matrix4x4R& pMatrix)
{
	_space.toMatrix4_4(pMatrix);
	pMatrix.GetW(3, 0) = _space.m_postion.x;
	pMatrix.GetW(3, 1) = _space.m_postion.y;
	pMatrix.GetW(3, 2) = _space.m_postion.z;
}