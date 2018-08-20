#include "../include.h"
#include "NodePushHelper.h"

struct PosColorVertex
{
	float m_x;
	float m_y;
	float m_z;
	uint32_t m_abgr; 
	static bgfx::VertexDecl ms_decl;
};
 

static PosColorVertex PlaneVertexs[] =
{
	{ 0.0f	   ,  0.0f		 ,  0.0f		, 0xff000000 },
	{ 10000.0f ,  0.0f		 ,  0.0f		, 0xff0000ff },
	{ -10000.0f,  0.0f		 ,  0.0f		, 0xff00ff00 },
	{ 0.0f	   ,  0.0f		 ,  10000.0f	, 0xff00ffff },
	{ 0.0f	   ,  0.0f		 ,   -10000.0f	, 0xffff0000 },
	{ 10000.0f ,  0.0f		 ,  10000.0f	, 0xffff00ff },
	{ 10000.0f ,  0.0f		 , -10000.0f	, 0xffffff00 },
	{ -10000.0f,  0.0f		 ,  10000.0f	, 0xffffffff },
	{ -10000.0f,  0.0f		 , -10000.0f	, 0xffffffff },
};

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
	 
	plane.matrixR(renderData.mtx);
	

	
}

void push(BOX_NODE& box)
{

}