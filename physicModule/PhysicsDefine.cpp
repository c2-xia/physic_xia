#include "PhysicsDefine.h"

PhysicsDefine PhysicsDefine::Instance;

//重力加速度
real PhysicsDefine::getG()
{
	return -9.8f;
}