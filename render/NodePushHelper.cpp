#include "../include.h"
#include "NodePushHelper.h"


extern std::list<IRenderAble> g_RenderAbles;
static float PLANE_W = 20.0f;
static PosColorVertex PlaneVertexs[] =
{
	{ 0.0f	   ,  0.0f		 ,  0.0f		, 0xffffffff },
	{ 10000.0f ,  0.0f		 ,  0.0f		, 0xffffff00 },
	{-10000.0f,  0.0f		 ,  0.0f		, 0xffffff00 },
	{ 0.0f	   ,  0.0f		 ,  10000.0f	, 0xffffffff },
	{ 0.0f	   ,  0.0f		 , -10000.0f	, 0xffffffff },
	{ 10000.0f ,  0.0f		 ,  10000.0f	, 0xffffffff },
	{ 10000.0f ,  0.0f		 , -10000.0f	, 0xffffffff },
	{-10000.0f,  0.0f		 ,  10000.0f	, 0xffffffff },
	{-10000.0f,  0.0f		 , -10000.0f	, 0xffffffff },

	//内圈的点
	{ PLANE_W ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{-PLANE_W ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{ 0.0f	 ,  0.0f	 ,  PLANE_W	, 0xffffffff },
	{ 0.0f	 ,  0.0f	 , -PLANE_W	, 0xffffffff },
	{ PLANE_W ,  0.0f	 ,  PLANE_W	, 0xffffffff },
	{ PLANE_W ,  0.0f	 , -PLANE_W	, 0xffffffff },
	{-PLANE_W ,  0.0f	 ,  PLANE_W	, 0xffffffff },
	{-PLANE_W ,  0.0f	 , -PLANE_W	, 0xffffffff },
};


static const uint16_t s_PlaneLineList[] =
{
	0,1, 
	0,2,
	0,3,
	0,4,
	0,5,
	0,6,
	0,7,
	0,8,
	//最外圈
	3,5,
	5,1,
	1,6,
	6,4,
	4,8,
	8,2,
	2,7,
	7,3,
	//内圈
	3 + 8,5 + 8,
	5 + 8,1 + 8,
	1 + 8,6 + 8,
	6 + 8,4 + 8,
	4 + 8,8 + 8,
	8 + 8,2 + 8,
	2 + 8,7 + 8,
	7 + 8,3 + 8,
};

void push(Plane& plane)
{
	if (plane.getDirty())
	{
		IRenderAble& renderData= plane.renderData;		 
		renderData.s_ptState = BGFX_STATE_PT_LINES;
		plane.matrixR(renderData.mtx);
		renderData.m_vbh = bgfx::createVertexBuffer( 
			bgfx::makeRef(PlaneVertexs, sizeof(PlaneVertexs))
			, PosColorVertex::ms_decl
		);
		renderData.ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(s_PlaneLineList, sizeof(s_PlaneLineList))
		);  
		plane.setDirty(false);
	} 
	g_RenderAbles.push_back(plane.renderData);
}

void push(BOX_NODE& box)
{

}