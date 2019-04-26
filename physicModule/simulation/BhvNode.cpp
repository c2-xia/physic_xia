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
	CollierType::Enum eType = (CollierType::Enum)(_collider)->_type;
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


InsertTestState::Enum BHV_Node::getState(BHV_Node* other)
{
	Vector3R dDistance = center - other->center;
	real len = dDistance.len();
	if (len > (radius + other->radius))
	{
		return InsertTestState::eOut;
	}
	else if (len <= xia_math::xia_abs(radius - other->radius))
	{
		return InsertTestState::eContain;
	}
	else
	{
		return InsertTestState::eCross;
	}
}
 

BHV_Node* BHV_Node::CalNewNode(BHV_Node* a, BHV_Node* b)
{
	Vector3R dDistance = a->center - b->center;
	real len = dDistance.len();
	real new_radius = (len + ( a->radius + b->radius ))/2;

	Vector3R new_Center = b->center + dDistance / 2;

	BHV_Node* result = new BHV_Node(NULL);
	result->radius = new_radius;
	result->center = new_Center;

	return result;
}
BhvList::~BhvList()
{
	//������ʱ��BhvTreeȥ�����ڵ�
	/*auto it = _list.begin();
	for (; it != _list.end(); it++)
	{
		delete *it;
	}*/
}

void BhvList::Push(BHV_Node* pNode)
{
	_STL_ASSERT(pNode, "BhvList::Push; pNode cant be null");
	pNode->cal_BHV();
	_list.push_back(pNode);
}


BhvTree::BhvTree(BhvList& bhv_list):pRoot(NULL)
{
	std::size_t size = bhv_list._list.size();
	auto it = bhv_list._list.begin();
	if (this->pRoot == NULL)
	{
		this->pRoot = *it;		 
	}
	for (; it != bhv_list._list.end();it++)
	{
		push(*it);
	}	
}


BhvTree::~BhvTree()
{ 
	//����������� 
	std::vector<BHV_Node*> parentList;
	 
	parentList.push_back(pRoot);
	while (!parentList.empty())
	{
		std::vector<BHV_Node*> TempList;
		for (size_t i = 0; i < parentList.size(); i++)
		{
			BHV_Node* p_parent = parentList[i];
			if (p_parent->left)
			{ 
					TempList.push_back(p_parent->left);
			}

			if (p_parent->right)
			{ 
					TempList.push_back(p_parent->right); 
			}
			delete p_parent;
		}
		parentList = TempList;
	}
}
 
 


BHV_Node* getNewTree(BHV_Node* root, BHV_Node* left , BHV_Node* right)
{ 
	root->left = left;
	root->right = right;
	return root;
}

void BhvTree::push(BHV_Node* node)
{
	//����кܶ����ײ�壬ÿʱÿ�̶��ڽ��棬����ʵ����bhv��һ�����嶼û�У�
	//���ʱ��Ӧ�ù���һ����΢��һ���İ�Χ�У�Ȼ����Щ��ײ�干��һ����Χ��
	//������ʵ����ʵ�������������棬����ʱʱ�̿̽��������ǲ����ܳ��ֵġ�
	//�ڹ�����ײ��ʱ��Ӧ�ü�⣬�����������ڳ���һ��ʼ��ײ��һ��

	//���������������Ҳ����Ǻܶ���ײ��ÿʱÿ�̽�����һ������


	if (this->pRoot == node)
		return;
	if (this->pRoot == NULL)
	{
		this->pRoot = node;
		return;
	}

	//����������� 
	std::vector<BHV_Node*> parentList;
	 
	InsertTestState::Enum states[3] = { InsertTestState::eInvalide,InsertTestState::eInvalide,InsertTestState::eInvalide };
	states[0] = pRoot->getState(node);
	if ( states[0] == InsertTestState::eOut )
	{
		BHV_Node* new_node = BHV_Node::CalNewNode(pRoot, node);
		pRoot = getNewTree(new_node, pRoot, node);
		return;
	}
	else if(states[0] == InsertTestState::eInContain)
	{ 
		pRoot = getNewTree(node, pRoot, NULL);
		return;
	}

	if (pRoot->left == NULL && pRoot->right == NULL)
	{
		if (states[0] == InsertTestState::eContain)
		{
			pRoot->left = node;
		}
		else if (states[0] == InsertTestState::eCross)
		{
			BHV_Node* new_node = BHV_Node::CalNewNode(pRoot, node);
			pRoot = getNewTree(new_node, pRoot, node);
		}
		return;
	}
	 
	parentList.push_back(pRoot); 
	while (!parentList.empty())
	{ 
		std::vector<BHV_Node*> TempList;
		for (size_t i = 0; i < parentList.size(); i++)
		{
			BHV_Node* p_parent = parentList[i];
			if (p_parent->left)
			{
				states[0] = p_parent->left->getState(node);
				if (states[0] == InsertTestState::eOut)
				{
					BHV_Node* new_node = BHV_Node::CalNewNode(p_parent->left, node); 
					p_parent->left = getNewTree(new_node, p_parent->left, node);
					return;
				}
				else if (states[0] == InsertTestState::eInContain)
				{
					p_parent->left = getNewTree( node, p_parent->left, NULL);
					return;
				}else if (p_parent->left->left == NULL && p_parent->left->right == NULL)
				{
					if (states[0] == InsertTestState::eContain)
					{
						p_parent->left->left = node;
					}
					else if (states[0] == InsertTestState::eCross)
					{
						BHV_Node* new_node = BHV_Node::CalNewNode(p_parent->left, node);
						p_parent->left = getNewTree(new_node, p_parent->left, node);
					}
					return;
				}else
					TempList.push_back(p_parent->left);
			}

			if (p_parent->right)
			{
				states[0] = p_parent->right->getState(node);
				if (states[0] == InsertTestState::eOut)
				{
					BHV_Node* new_node = BHV_Node::CalNewNode(p_parent->right, node);
					p_parent->right = getNewTree(new_node, p_parent->right, node);
					return;
				}
				else if (states[0] == InsertTestState::eInContain)
				{
					p_parent->right = getNewTree(node, p_parent->right, NULL);
					return;
				}
				else if (p_parent->right->left == NULL && p_parent->right->right == NULL)
				{
					if (states[0] == InsertTestState::eContain)
					{
						p_parent->right->left = node;
					}
					else if (states[0] == InsertTestState::eCross)
					{
						BHV_Node* new_node = BHV_Node::CalNewNode(p_parent->right, node);
						p_parent->right = getNewTree(new_node, p_parent->right, node);
					}
					return;
				}
				else
					TempList.push_back(p_parent->right);

			}  
		}
		parentList = TempList;
	}	
}


void BhvTree::getContactFroces(std::vector<contactForcePaire>& out)
{

}
