#include "../include.h"
#include "collider.h"
#include "BoxCollider.h"

#include "ColliderManager.h"

ColliderManager ColliderManager::Instance;

ColliderManager::ColliderManager()
{
	int i = 0;
}


Collider* ColliderManager::Create(CollierType::Enum eType)
{
	switch (eType)
	{
		case CollierType::BoxCollider:
		{
			return CreateBoxCollider();
			break;
		}
	default:
		return NULL;
		break;
	}
	return NULL;
}

BoxCollider* ColliderManager::CreateBoxCollider()
{
	BoxCollider* collider = new BoxCollider();
	collider->_type = CollierType::BoxCollider;
	_Colliders.push_back((Collider*)collider);
	return collider;
}


bool ColliderManager::Destory(Collider* collider)
{
	_Colliders.remove(collider);
	delete collider;
	return true;
}
