 
/*
 * Copyright 2011-2018 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#include "common.h"
#include "bgfx_utils.h"
#include "imgui/imgui.h"

#include "../include.h"
#include "../NodeRender.h"
#include "../NodePushHelper.h"
#include <list>

void RenderLoop(bgfx::ProgramHandle& m_program);
extern std::list<IRenderAble> g_RenderAbles;
bgfx::VertexDecl PosColorVertex::ms_decl;

void mainInit();
namespace
{
	 
 
static const char* s_ptNames[]
{
	"Triangle List",
	"Triangle Strip",
	"Lines",
	"Points",
};

static const uint64_t s_ptState[]
{
	BGFX_STATE_PT_TRISTRIP,
	UINT64_C(0),
	BGFX_STATE_PT_LINES,
	BGFX_STATE_PT_POINTS,
};



class ExampleCubes : public entry::AppI
{
public:
	ExampleCubes(const char* _name, const char* _description)
		: entry::AppI(_name, _description)
		, m_pt(0)
		, m_r(true)
		, m_g(true)
		, m_b(true)
		, m_a(true)
	{
	}

	void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
	{
		Args args(_argc, _argv);

		m_width  = _width;
		m_height = _height;
		m_debug  = BGFX_DEBUG_PROFILER;
		m_reset  = BGFX_RESET_VSYNC;

		bgfx::Init init;
		init.type     = args.m_type;
		init.vendorId = args.m_pciId;
		init.resolution.width  = m_width;
		init.resolution.height = m_height;
		init.resolution.reset  = m_reset;
		bgfx::init(init);

		// Enable debug text.
		bgfx::setDebug(m_debug);

		// Set view 0 clear state.
		bgfx::setViewClear(0
			, BGFX_CLEAR_COLOR|BGFX_CLEAR_DEPTH
			, 0x303030ff
			, 1.0f
			, 0
			);
		mainInit();
		// Create vertex stream declaration.
		PosColorVertex::init();
		m_program = loadProgram("vs_cubes", "fs_cubes");
		  

		imguiCreate();
	}

	virtual int shutdown() override
	{
		imguiDestroy();

		// Cleanup.
		bgfx::destroy(m_program);
		  

		// Shutdown bgfx.
		bgfx::shutdown();

		return 0;
	}


	bool update() override
	{
		if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState) )
		{
			imguiBeginFrame(m_mouseState.m_mx
				,  m_mouseState.m_my
				, (m_mouseState.m_buttons[entry::MouseButton::Left  ] ? IMGUI_MBUT_LEFT   : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Right ] ? IMGUI_MBUT_RIGHT  : 0)
				| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
				,  m_mouseState.m_mz
				, uint16_t(m_width)
				, uint16_t(m_height)
				);
			if (m_mouseState.m_buttons[entry::MouseButton::Left])
			{

			}

			showExampleDialog(this);

			ImGui::SetNextWindowPos(
				  ImVec2(m_width - m_width / 5.0f - 10.0f, 10.0f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::SetNextWindowSize(
				  ImVec2(m_width / 5.0f, m_height / 3.5f)
				, ImGuiCond_FirstUseEver
				);
			ImGui::Begin("Settings"
				, NULL
				, 0
				);

			ImGui::Checkbox("Write R", &m_r);
			ImGui::Checkbox("Write G", &m_g);
			ImGui::Checkbox("Write B", &m_b);
			ImGui::Checkbox("Write A", &m_a);

			ImGui::Text("Primitive topology:");
			ImGui::Combo("", (int*)&m_pt, s_ptNames, BX_COUNTOF(s_ptNames) );

			ImGui::End();

			imguiEndFrame();

			 

			float at[3]  = { 0.0f, 0.0f,   0.0f };
			float eye[3] = { 0.0f,  1000.0f,0.0f };
			float up[3] = { 0.0f,  0.0f,-1000.0f };
			// Set view and projection matrix for view 0.
			{
				float view[16];
				bx::mtxLookAt(view, eye, up);

				float proj[16];
				bx::mtxProj(proj, 120.0f, float(m_width)/float(m_height), 0.1f, 10000.0f, bgfx::getCaps()->homogeneousDepth);
				bgfx::setViewTransform(0, view, proj);

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height) );
			}

			// This dummy draw call is here to make sure that view 0 is cleared
			// if no other draw calls are submitted to view 0.
			bgfx::touch(0);

			RenderLoop(m_program);

			bgfx::frame();
			

			return true;
		}

		return false;
	}



	static entry::MouseState m_mouseState;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;   
	int64_t m_timeOffset;
	int32_t m_pt;
	bgfx::ProgramHandle m_program;
	bool m_r;
	bool m_g;
	bool m_b;
	bool m_a;
};
entry::MouseState ExampleCubes::m_mouseState;

} // namespace 
const  entry::MouseState& getMouseState()
{
	return ExampleCubes::m_mouseState;
}
ENTRY_IMPLEMENT_MAIN(ExampleCubes, "01-cubes", "Rendering simple static mesh.");
