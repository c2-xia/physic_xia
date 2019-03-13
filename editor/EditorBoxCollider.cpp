#include "../include.h"
#include "BoxNode.h"
#include "../physicModule/Collider.h"
#include "../physicModule/BoxCollider.h"
#include "../physicModule/ColliderManager.h"
#include "EditorBoxCollider.h"



EditorBoxCollider::EditorBoxCollider():_boxCollider(NULL)
{
	

}


EditorBoxCollider::~EditorBoxCollider()
{

}

void EditorBoxCollider::process()
{
	_STL_ASSERT(_boxCollider != NULL, "_boxCollider cant be null");
	_STL_ASSERT(_boxCollider->rb != NULL, "_boxCollider.rb cant be null");
	SpaceRepresent& space_rb = _boxCollider->rb->_space;
	 
	SpaceRepresent space = space_rb * _boxCollider->_space;

	_boxNodeView._scale = _boxCollider->_size;
	_boxNodeView._space = space;
	_boxNodeView._bMatrixDirty = true;
}


