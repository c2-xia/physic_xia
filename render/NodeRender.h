//#define ENTRY_CONFIG_IMPLEMENT_MAIN 0
#include <bx/macros.h>
namespace entry
{
	class BX_NO_VTABLE AppI;
	entry::AppI*  RenderInit(int _argc, const char* const* _argv);
	bool RenderUpdate(entry::AppI* _app);
	void renderExit(entry::AppI* _app);
}

 
struct DrawAble
{

};

void renderTest()
{

}
