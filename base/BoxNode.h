#ifndef BOX_NODE_H
#define BOX_NODE_H

#include "Node.h"

struct BOX_NODE:public Node
{
	BOX_NODE() :_bDirty(true) {}
	Vector3R _scale;
	/*
	nDirection ：0表示x轴，1表示y轴,2表示轴
	*/
	void set(Vector3R bottom,unsigned char nDirection=1);


	//render code 
	bool	 _bDirty;
	void matrixR(Matrix4x4R& pMatrix);
	
	void setDirty(bool bDirty) { _bDirty = bDirty; }
	bool getDirty() { return _bDirty; };
	struct IRenderAble renderData;
};

#endif

