#include "include.h"
#include "render/NodePushHelper.h"
#include <entry/input.h>
#include "render/Camera.h"
#include "runtime/GlobalValues.h"
#include "editor/Input.h"
#include "editor/EventSystem.h"
#include "editor/CameraEdit.h"
#include "physicModule/simulation/M_Simulation.h"
#include "physicModule/collider.h"
#include "physicModule/BoxCollider.h"
#include "editor/EditorBoxCollider.h"
#include "physicModule/rigidbody.h"
#include "physicModule/PhysicsDefine.h"
#include "physicModule/ColliderManager.h"
#include "base/QuaternionHelper.h"

template<class T>
int LENGTH(T& arr)
{
	//cout << sizeof(arr[0]) << endl;
	//cout << sizeof(arr) << endl;
	return sizeof(arr) / sizeof(arr[0]);
}

std::list<IRenderAble> g_RenderAbles;

Camera& getCubesCamera();

CameraEdit cameraEdit;

M_Simulation g_simulation;

EditorBoxCollider vecBox[2];
Rigidbody    rb[2];

void mainInit(unsigned int width,unsigned int height)
{
	GlobalValues::instance.width  = width ;
	GlobalValues::instance.height = height;
	GlobalValues::instance.G = -9.8f;
	cameraEdit._pCamera = &getCubesCamera();

	EventSystem::Instance.addRightMouseLisener(&cameraEdit);
	EventSystem::Instance.addWheelListener(&cameraEdit);
	
	g_simulation.addRigidbody(&rb[0]);	
	g_simulation.addRigidbody(&rb[1]);
	vecBox[0]._boxCollider = (BoxCollider*)ColliderManager::Instance.Create(CollierType::Enum::BoxCollider);
	vecBox[1]._boxCollider = (BoxCollider*)ColliderManager::Instance.Create(CollierType::Enum::BoxCollider);
	rb[0].addCollider(vecBox[0]._boxCollider);
	rb[1].addCollider(vecBox[1]._boxCollider);
	rb[1]._isLock = true;
	vecBox[0]._boxCollider->rb->_speed.Set(0, -1, 0);
	vecBox[1]._boxCollider->rb->_speed.Set(0, -1, 0);
	Vector3R rotateSpeed;
	rotateSpeed.Set(0, 90, 0);
	//vecBox[0]._boxCollider.rb->_AngleSpeed = rotateSpeed;
	vecBox[0]._boxCollider->_size.Set(1, 1, 1);
	vecBox[0]._boxCollider->_space.m_postion.Set(0, 2, 0);
	vecBox[1]._boxCollider->_size.Set(1, 1, 1);
	vecBox[1]._boxCollider->_space.m_postion.Set(0,0, 0);


}


void pushRenders();

void processEvent();

void LogicMain()
{
	//vecBox[0]._boxCollider.rb->_acceleratedSpeed.y = PhysicsDefine::Instance.getG();
	processEvent();

	pushRenders();
		
}

void pushRenders()
{
	/*
	1.显示一个平面
	2.让一个方块放在平面上
	*/
	static Plane	_plane;
	//static BOX_NODE	_boxNode;
	static bool b_init = false;
	if (!b_init)
	{
		_plane._up.y = 1;
		//_boxNode._scale.Set(1, 1, 1);
		//_boxNode.set({ 0.0f,0.0f,0.0f }, 1);
		b_init = true;
	}
	push(_plane);
	int size = LENGTH(vecBox);
	for (int i = 0; i < size; i++)
	{
		vecBox[i].process();
		 
		push(vecBox[i]._boxNodeView);
	}
	
}

void processEvent()
{
	EventSystem::Instance.process();



	g_simulation.process(1.0f/60);	
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

