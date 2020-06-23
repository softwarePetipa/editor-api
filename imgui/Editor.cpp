#include "native.h"
#include "GL.h"
#include "imgui.h"
#include "text.h"

extern petipa::imgui::Resources res;
extern petipa::imgui::Context ctx;

petipa::imgui::Editor::Editor() :
	button_exit("exit", 130,40),
	button_alert("test", 130,40)
{
}

petipa::imgui::Editor::~Editor()
{
}

void petipa::imgui::Editor::loop_step()
{
	ctx.layout.spacing = 10;

	// Render *and* intereact with UI elements.
	petipa::imgui::layout_start (Layout::Type::VERTICAL_DOWN_ALIGN_RIGHT, res.width, 0);
	if (do_button (button_alert))
		petipa::api::native::alert ("Test", "Hi, there.");
	if (do_button (button_exit))
		res.running = false;
}

// vim600:foldmethod=syntax:foldnestmax=1:
