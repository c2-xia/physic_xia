#ifndef BOX_NODE_H
#define BOX_NODE_H

#include "Node.h"

struct BOX_NODE:public Node
{
	Vector3R _scale;
	/*
	nDirection ��0��ʾx�ᣬ1��ʾy��,2��ʾ��
	*/
	void set(Vector3R bottom, Vector3R scale,unsigned char nDirection=0);
};

#endif

