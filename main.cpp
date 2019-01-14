#include "include.h"
#include "render/NodePushHelper.h"
#include <entry/input.h>
#include "render/Camera.h"
#include "runtime/GlobalValues.h"
#include "editor/Input.h"
#include "editor/EventSystem.h"
#include "editor/CameraEdit.h"

std::list<IRenderAble> g_RenderAbles;

Camera& getCubesCamera();

CameraEdit cameraEdit;


void mainInit(unsigned int width,unsigned int height)
{
	GlobalValues::instance.width  = width ;
	GlobalValues::instance.height = height;

	cameraEdit._pCamera = &getCubesCamera();
	EventSystem::Instance.addRightMouseLisener(&cameraEdit);
	EventSystem::Instance.addWheelListener(&cameraEdit);
	 
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
		_boxNode._scale.Set(1, 1, 1);
		_boxNode.set({ 0.0f,0.0f,0.0f }, 1);
		b_init = true;
	}
	push(_plane);
	push(_boxNode);
}

void processEvent()
{
	EventSystem::Instance.process();


	
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

