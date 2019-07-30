#include "collider.h"
#include "rigidbody.h"



Rigidbody::Rigidbody()
{
	this->mass = 1;
	this->_acceleratedAngleSpeed = Vector3R::Zero();
	this->_acceleratedSpeed = Vector3R::Zero();
	this->_AngleSpeed = Vector3R::Zero();
	this->_isLock = false;
	this->_speed = Vector3R::Zero();
 
}

void Rigidbody::addCollider(class Collider* collider)
{
	_STL_ASSERT(collider != NULL, "collider cant be null");
	this->_colliders.push_back(collider);
	collider->rb = this;
}