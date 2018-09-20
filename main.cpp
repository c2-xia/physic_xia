#include "include.h"
#include "render/NodePushHelper.h"
#include <entry/input.h>

std::list<IRenderAble> g_RenderAbles;

 
void mouseDown(const void* _userData)
{
	int i = 0;
}
void mouseUp(const void* _userData)
{
	int i = 0;
}
//static const InputBinding m_s_bindings[] =
//{
//	{ entry::Key::PageDown,         entry::Modifier::None,  2, mouseDown, "mouseDown"                              },
//	{ entry::Key::PageUp  ,         entry::Modifier::None,  2, mouseUp, "mouseUp"                                },
//	{ entry::Key::KeyA  ,         entry::Modifier::None,  2, mouseUp, "mouseUp"                                },
//	INPUT_BINDING_END
//};

void mainInit()
{
	//inputAddBindings("mainInput", m_s_bindings);


}


const  entry::MouseState& getMouseState();
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
	static bool bPressed = false;
	if (getMouseState().m_buttons[entry::MouseButton::Enum::Left])
	{
		mouseDown(&getMouseState());
		bPressed = true;
	}
	else if (bPressed == true)
	{
		mouseUp(&::getMouseState());
		bPressed = false;
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

