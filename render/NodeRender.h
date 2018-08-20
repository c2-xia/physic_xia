//#define ENTRY_CONFIG_IMPLEMENT_MAIN 0
#include <bx/macros.h>
#include "bgfx_utils.h"
namespace entry
{
	class BX_NO_VTABLE AppI;
	entry::AppI*  RenderInit(int _argc, const char* const* _argv);
	bool RenderUpdate(entry::AppI* _app);
	void renderExit(entry::AppI* _app);
}

 
struct IRenderAble
{
	float mtx[16];
	bgfx::VertexBufferHandle m_vbh;
	bgfx::IndexBufferHandle ibh;
	uint64_t   s_ptState;

	void submit(bgfx::ProgramHandle& m_program,
		bool m_r =true,
		bool m_g = true,
		bool m_b = true,
		bool m_a = true); 
};
