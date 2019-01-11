#include "include.h"
#include "render/NodePushHelper.h"
#include <entry/input.h>
#include "render/Camera.h"
#include "runtime/GlobalValues.h"

std::list<IRenderAble> g_RenderAbles;

const  entry::MouseState& getMouseState();
Camera& getCubesCamera();

Vector3R leftMousePosCash;
bool leftMousePress = false;
void LeftMouseDownEvent();
void LeftMouseMoveEvent(Vector3R start, Vector3R end);
void LeftMouseUpEvent();


void mainInit(unsigned int width,unsigned int height)
{
	GlobalValues::instance.width = width;
	GlobalValues::instance.height = height;
}


bool onLeftMouse()
{ 
	if (!leftMousePress)
	{
		leftMousePress = true;
		const  entry::MouseState& mState = getMouseState();
		leftMousePosCash.Set((real)mState.m_mx, (real)mState.m_my, (real)mState.m_mz);

		LeftMouseDownEvent();
		return true;
	}
	return false;
}

void onLeftMouseMove()
{
	Vector3R nowPos; 
	nowPos.Set((real)getMouseState().m_mx, (real)getMouseState().m_my, (real)getMouseState().m_mz);
	
	Vector3R dertaPos = nowPos - leftMousePosCash;

	LeftMouseMoveEvent(leftMousePosCash,nowPos);
	leftMousePosCash = nowPos;
}

void onLeftMouseUp()
{
	leftMousePress = false;

	leftMousePosCash = Vector3R::Zero();
	LeftMouseUpEvent();
}

void LeftMouseDownEvent()
{
	getCubesCamera().onMousePress();
}

void LeftMouseMoveEvent(Vector3R start, Vector3R end)
{
	getCubesCamera().onMouseMove(start,end);
}

void LeftMouseUpEvent()
{
	getCubesCamera().onMouseUp();
}




void pushRenders();
void processEvent();

void LogicMain()
{
	pushRenders();
	processEvent();	
}
void pushRenders()
{
	/*
	1.显示一个平面
	2.让一个方块放在平面上
	*/
	static Plane	_plane;
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

void processEvent()
{
	if (getMouseState().m_buttons[entry::MouseButton::Enum::Left] )
	{
		if ( ! onLeftMouse() )
		{
			onLeftMouseMove();
		}
	}
	else
	{

	}

 
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

