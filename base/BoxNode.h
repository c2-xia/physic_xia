#ifndef BOX_NODE_H
#define BOX_NODE_H

#include "Node.h"

struct BOX_NODE:public Node
{
	BOX_NODE() :_bMatrixDirty(true),
		_bVertexDirty(true),
		_bIndexDirty(true){}
	Vector3R _scale;
	/*
	nDirection ��0��ʾx�ᣬ1��ʾy��,2��ʾz��
	*/
	void set(Vector3R bottom,unsigned char nDirection=1);


	//render code 
	bool	 _bMatrixDirty;
	bool	 _bVertexDirty;
	bool	 _bIndexDirty;
	void matrixR(Matrix4x4R& pMatrix);
	 

	struct IRenderAble renderData;

};

#endif

