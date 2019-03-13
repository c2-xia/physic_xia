#include "../../include.h"
#include "../collider.h"
#include "../BoxCollider.h"
#include "../ColliderManager.h"
#include "BhvNode.h"


BHV_Node::BHV_Node(Collider* collider):right(NULL),left(NULL)
{
	this->_collider = collider;
}

void BHV_Node::cal_BHV()
{
	CollierType::Enum eType = (CollierType::Enum)_collider->_type;
	switch (eType)
	{
		case CollierType::BoxCollider:
		{
			BoxCollider* boxCollider = (BoxCollider*)_collider;
			_STL_ASSERT(boxCollider != NULL, "_boxCollider cant be null");
			_STL_ASSERT(boxCollider->rb != NULL, "_boxCollider.rb cant be null");
			SpaceRepresent& space_rb = boxCollider->rb->_space;

			SpaceRepresent space = space_rb * boxCollider->_space;
			this->center = space.m_postion;
			Vector3R& size = boxCollider->_size;
			this->radius = xia_math::xia_sqrt(size.x*size.x + size.y*size.y + size.z* size.z);
			break;
		}
		default:
			break;
	}
}
 
BhvList::~BhvList()
{
	auto it = _list.begin();
	for (; it != _list.end(); it++)
	{
		delete *it;
	}
}

void BhvList::Push(BHV_Node* pNode)
{
	_STL_ASSERT(pNode, "BhvList::Push; pNode cant be null");
	pNode->cal_BHV();
	_list.push_back(pNode);
}


BhvTree::BhvTree(BhvList& bhv_list)
{
	std::size_t size = bhv_list._list.size();
	
	
}