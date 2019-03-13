#ifndef COLLIDER_H
#define COLLIDER_H

#include "rigidbody.h"
class Collider
{
public:
	Collider():rb(NULL),_type(NULL) {};
	short _type;
	Rigidbody* rb;
};



#endif