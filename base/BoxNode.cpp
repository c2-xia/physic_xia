#include "base.h"
#include "BoxNode.h"

void BOX_NODE::set(Vector3R bottom, Vector3R scale,unsigned char nDirection)
{
	if (nDirection >= 0 && nDirection < 3)
	{
		_pos = bottom;
		_pos[nDirection] += scale[nDirection];
	}
}