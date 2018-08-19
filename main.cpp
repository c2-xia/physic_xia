#include "include.h"
#include "render/NodePushHelper.h"

std::list<IRenderAble> g_RenderAbles;

void LogicMain()
{
	/*
	1.��ʾһ��ƽ��
	2.��һ���������ƽ����
	*/
	Plane		_plane;
	BOX_NODE	_boxNode;
	_plane._up.y = 1;
	_boxNode.set({ 0.0f,0.0f,0.0f }, {1.0f,1.0f,1.0f }, 1);


	push(_plane);
	push(_boxNode);
}
 
void RenderLoop(bgfx::ProgramHandle& m_program)
{ 
	LogicMain();
	auto it = g_RenderAbles.begin();
	for (; it != g_RenderAbles.end(); it++)
	{
		it->submit(m_program);
	}
}

