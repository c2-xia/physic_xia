#include "include.h"
#include "render/NodePushHelper.h"

std::list<IRenderAble> g_RenderAbles;

void LogicMain()
{
	/*
	1.显示一个平面
	2.让一个方块放在平面上
	*/
	static Plane		_plane;
	static BOX_NODE	_boxNode;
	static bool b_init = false;
	if (!b_init)
	{
		_plane._up.y = 1;
		_boxNode.set({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, 1);
		b_init = true;
	}
	push(_plane);
	push(_boxNode);
}
 
void RenderLoop(bgfx::ProgramHandle& m_program)
{ 
	g_RenderAbles.clear();
	LogicMain();
	auto it = g_RenderAbles.begin();
	for (; it != g_RenderAbles.end(); it++)
	{
		it->submit(m_program);
	}
	
}

