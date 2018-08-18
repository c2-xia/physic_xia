#include "render/NodeRender.h"


static bool b_quit = false;
namespace entry
{ 
	int main(int _argc, const char* const* _argv)
	{
		entry::AppI* p_app = RenderInit(_argc, _argv);

		while (!b_quit)
		{

			RenderUpdate(p_app);
		}
		renderExit(p_app);

		return 0;
	}
}