#include "../../include.h"
#include "../rigidbody.h"
#include "../../base/QuaternionHelper.h"
#include "collider.h"
#include "BoxCollider.h"
#include "../ColliderManager.h"
#include "BhvNode.h"
#include "../runtime/GlobalValues.h"
#include "M_Simulation.h"


void M_Simulation::process(real rDertaTime)
{

	std::list<Collider*>& colliders = ColliderManager::Instance.getColliders();
	
	//build bvh
	{
		BhvList bhv_list;
		auto it = colliders.begin();

		for (; it != colliders.end(); it++)
		{
			bhv_list.Push(new BHV_Node(*it));
		}

		BhvTree tree(bhv_list);
		std::vector<contactForcePaire> forces;
		tree.getContactFroces(forces);
		
	}
	
	auto it = _rigidbodys.begin();
	for (; it != _rigidbodys.end(); it++)
	{
		Rigidbody* rb = (*it);
		_STL_ASSERT(rb != NULL,"rb cant be null");
		rb->_acceleratedSpeed = Vector3R(0,GlobalValues::instance.G,0);
		rb->_speed += rb->_acceleratedSpeed*rDertaTime;
		
		
		rb->_AngleSpeed += rb->_acceleratedAngleSpeed* rDertaTime;
		Vector3R rotateAngle = rb->_AngleSpeed * rDertaTime * xia_math::Deg2Rad;
		QuaternionR test =  EulerToQuaternion(rotateAngle);
		if (!rb->_isLock)
		{
			rb->_space.m_postion += rb->_speed*rDertaTime;
			rb->_space.m_rotatin = rb->_space.m_rotatin*test;

			rb->_space.m_rotatin = Normalize(rb->_space.m_rotatin);
		}		 
		rb->_acceleratedSpeed = Vector3R::Zero();
		rb->_acceleratedAngleSpeed = Vector3R::Zero();	
	}
	 
}

std::list<class Rigidbody*> const & M_Simulation::getRigidbodys()
{
	return this->_rigidbodys;
}

void M_Simulation::addRigidbody(class Rigidbody* rb)
{
	this->_rigidbodys.push_back(rb);
}