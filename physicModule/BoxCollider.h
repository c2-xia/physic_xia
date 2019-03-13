#ifndef BOX_COLLIDER_H
#define BOX_COLLIDER_H

#include "collider.h"

class BoxCollider:public Collider
{ 
friend class ColliderManager;
public:
	Vector3R _size;
	SpaceRepresent _space;	 
private:
	BoxCollider() {};
};


#endif //BOX_COLLIDER_H