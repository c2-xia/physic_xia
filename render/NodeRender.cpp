
#include "NodeRender.h"

#include "common.h"


void IRenderAble::submit(bgfx::ProgramHandle& m_program,
	bool m_r,
	bool m_g,
	bool m_b,
	bool m_a)
{
	uint64_t state = 0
		| (m_r ? BGFX_STATE_WRITE_R : 0)
		| (m_g ? BGFX_STATE_WRITE_G : 0)
		| (m_b ? BGFX_STATE_WRITE_B : 0)
		| (m_a ? BGFX_STATE_WRITE_A : 0)
		| BGFX_STATE_WRITE_Z

		| BGFX_STATE_DEPTH_TEST_LESS
		| BGFX_STATE_CULL_CW
		| BGFX_STATE_MSAA
		| s_ptState
		; 
	bgfx::setTransform(mtx.getPtr());
	bgfx::setVertexBuffer(0, m_vbh);
	bgfx::setIndexBuffer(ibh);

	bgfx::setState(state);

	bgfx::submit(0, m_program);
}