#include "../include.h"
#include "NodePushHelper.h"

void push(Plane& plane)
{
	IRenderAble renderData;
	
	/*struct IRenderAble
	{
		float mtx[16];
		bgfx::VertexBufferHandle m_vbh;
		bgfx::IndexBufferHandle ibh;
		uint64_t   s_ptState;*/
	renderData.s_ptState = BGFX_STATE_PT_LINES;
	



	
}

void push(BOX_NODE& box)
{

}