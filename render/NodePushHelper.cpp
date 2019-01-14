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

	//内圈的点 1
	{ PLANE_W ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{-PLANE_W ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{ 0.0f	 ,  0.0f	 ,  PLANE_W	, 0xffffffff },
	{ 0.0f	 ,  0.0f	 , -PLANE_W	, 0xffffffff },
	{ PLANE_W ,  0.0f	 ,  PLANE_W	, 0xffffffff },
	{ PLANE_W ,  0.0f	 , -PLANE_W	, 0xffffffff },
	{-PLANE_W ,  0.0f	 ,  PLANE_W	, 0xffffffff },
	{-PLANE_W ,  0.0f	 , -PLANE_W	, 0xffffffff },
	//内圈的点 2
	{ PLANE_W * 2 ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{-PLANE_W * 2 ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{ 0.0f	 ,  0.0f	 ,  PLANE_W * 2	, 0xffffffff },
	{ 0.0f	 ,  0.0f	 , -PLANE_W * 2, 0xffffffff },
	{ PLANE_W * 2 ,  0.0f	 ,  PLANE_W * 2	, 0xffffffff },
	{ PLANE_W * 2,  0.0f	 , -PLANE_W * 2, 0xffffffff },
	{-PLANE_W * 2 ,  0.0f	 ,  PLANE_W * 2, 0xffffffff },
	{-PLANE_W * 2,  0.0f	 , -PLANE_W * 2	, 0xffffffff },


	//内圈的点 3
	{ PLANE_W * 3 ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{-PLANE_W * 3 ,  0.0f	 ,  0.0f	, 0xffffff00 },
	{ 0.0f	 ,  0.0f	 ,  PLANE_W * 3	, 0xffffffff },
	{ 0.0f	 ,  0.0f	 , -PLANE_W * 3, 0xffffffff },
	{ PLANE_W * 3 ,  0.0f	 ,  PLANE_W * 3	, 0xffffffff },
	{ PLANE_W * 3,  0.0f	 , -PLANE_W * 3, 0xffffffff },
	{-PLANE_W * 3 ,  0.0f	 ,  PLANE_W * 3, 0xffffffff },
	{-PLANE_W * 3,  0.0f	 , -PLANE_W * 3	, 0xffffffff },
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
	
	//内圈1
	3 + 8,5 + 8,
	5 + 8,1 + 8,
	1 + 8,6 + 8,
	6 + 8,4 + 8,
	4 + 8,8 + 8,
	8 + 8,2 + 8,
	2 + 8,7 + 8,
	7 + 8,3 + 8,
	//内圈2
	3 + 8 * 2,5 + 8 * 2,
	5 + 8 * 2,1 + 8 * 2,
	1 + 8 * 2,6 + 8 * 2,
	6 + 8 * 2,4 + 8 * 2,
	4 + 8 * 2,8 + 8 * 2,
	8 + 8 * 2,2 + 8 * 2,
	2 + 8 * 2,7 + 8 * 2,
	7 + 8 * 2,3 + 8 * 2,

	//内圈3
	3 + 8 * 3,5 + 8 * 3,
	5 + 8 * 3,1 + 8 * 3,
	1 + 8 * 3,6 + 8 * 3,
	6 + 8 * 3,4 + 8 * 3,
	4 + 8 * 3,8 + 8 * 3,
	8 + 8 * 3,2 + 8 * 3,
	2 + 8 * 3,7 + 8 * 3,
	7 + 8 * 3,3 + 8 * 3,
};

void push(Plane& plane)
{
	if (plane.getDirty())
	{
		IRenderAble& renderData= plane.renderData;		 
		renderData.s_ptState = BGFX_STATE_PT_LINES;
		plane.matrixR(renderData.mtx.getPtr());
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



//box_node start
float half_width = 10.0f;
static PosColorVertex BoxVertexs[] =
{
	{-half_width,  half_width,  half_width, 0xff000000 },
	{ half_width,  half_width,  half_width, 0xff0000ff },
	{-half_width, -half_width,  half_width, 0xff00ff00 },
	{ half_width, -half_width,  half_width, 0xff00ffff },
	{-half_width,  half_width, -half_width, 0xffff0000 },
	{ half_width,  half_width, -half_width, 0xffff00ff },
	{-half_width, -half_width, -half_width, 0xffffff00 },
	{ half_width, -half_width, -half_width, 0xffffffff },
};


static const uint16_t s_BoxLineList[] =
{
	 0,1,
	 1,2,
	 2,3,
	 3,0,

	 4,5,
	 5,6,
	 6,7,
	 7,4,

	 0,4,
	 1,5,
	 2,6,
	 3,7,
};


static const uint16_t s_BoxTriList[] =
{
	0, 1, 2, // 0
	1, 3, 2,
	4, 6, 5, // 2
	5, 6, 7,
	0, 2, 4, // 4
	4, 2, 6,
	1, 5, 3, // 6
	5, 7, 3,
	0, 4, 1, // 8
	4, 5, 1,
	2, 3, 6, // 10
	6, 3, 7,
};

void push(BOX_NODE& box)
{
	if (box.getDirty())
	{
		IRenderAble& renderData = box.renderData;
		renderData.s_ptState = UINT64_C(0);
		box.matrixR(renderData.mtx);
		renderData.m_vbh = bgfx::createVertexBuffer(
			bgfx::makeRef(BoxVertexs, sizeof(BoxVertexs))
			, PosColorVertex::ms_decl
		);
		renderData.ibh = bgfx::createIndexBuffer(
			bgfx::makeRef(s_BoxTriList, sizeof(s_BoxTriList))
		);
		box.setDirty(false);
	}
	g_RenderAbles.push_back(box.renderData);
}