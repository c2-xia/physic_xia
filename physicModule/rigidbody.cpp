#include "collider.h"
#include "rigidbody.h"




void Rigidbody::addCollider(class Collider* collider)
{
	_STL_ASSERT(collider != NULL, "collider cant be null");
	this->_colliders.push_back(collider);
	collider->rb = this;
}