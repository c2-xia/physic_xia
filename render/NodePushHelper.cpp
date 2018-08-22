#include "../include.h"
#include "NodePushHelper.h"


extern std::list<IRenderAble> g_RenderAbles;
static PosColorVertex PlaneVertexs[] =
{
	{ 0.0f	   ,  0.0f		 ,  0.0f		, 0xffffffff },
	{ 10000.0f ,  0.0f		 ,  0.0f		, 0xffffff00 },
	{ -10000.0f,  0.0f		 ,  0.0f		, 0xffffff00 },
	{ 0.0f	   ,  0.0f		 ,  10000.0f	, 0xffffffff },
	{ 0.0f	   ,  0.0f		 ,  -10000.0f	, 0xffffffff },
	{ 10000.0f ,  0.0f		 ,  10000.0f	, 0xffffffff },
	{ 10000.0f ,  0.0f		 , -10000.0f	, 0xffffffff },
	{ -10000.0f,  0.0f		 ,  10000.0f	, 0xffffffff },
	{ -10000.0f,  0.0f		 , -10000.0f	, 0xffffffff },
};


static const uint16_t s_PlaneLineList[] =
{
	0, 1, 
	0,2,
	0,3,
	0,4,
	0,5,
	0,6,
	0,7,
	0,8,
};

void push(Plane& plane)
{
	if (plane.getDirty())
	{

		IRenderAble& renderData= plane.renderData;

		/*struct IRenderAble
		{
			float mtx[16];
			bgfx::VertexBufferHandle m_vbh;
			bgfx::IndexBufferHandle ibh;
			uint64_t   s_ptState;*/
		renderData.s_ptState = BGFX_STATE_PT_LINES;

		plane.matrixR(renderData.mtx);

		renderData.m_vbh = bgfx::createVertexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(PlaneVertexs, sizeof(PlaneVertexs))
			, PosColorVertex::ms_decl
		);
		renderData.ibh = bgfx::createIndexBuffer(
			// Static data can be passed with bgfx::makeRef
			bgfx::makeRef(s_PlaneLineList, sizeof(s_PlaneLineList))
		); 
		plane.setDirty(false);
	} 
	g_RenderAbles.push_back(plane.renderData);
}

void push(BOX_NODE& box)
{

}