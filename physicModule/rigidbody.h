#ifndef XIA_RIGIDBODY_H
#define XIA_RIGIDBODY_H

#include "../include.h"

class Rigidbody
{
public:
	Rigidbody();
	real			mass;
	SpaceRepresent  _space;
	Vector3R		_speed;
	Vector3R		_acceleratedSpeed;
	Vector3R        _AngleSpeed;
	Vector3R        _acceleratedAngleSpeed;
	bool			_isLock;

	void addCollider(class Collider*);
private:
	std::list<class Collider*> _colliders;
};

#endif //!XIA_RIGIDBODY_H