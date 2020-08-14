#include "native.h"
#include "GL.h"
#include "imgui.h"
#include "text.h"
#include "icons/character.h"
#include "icons/eye.h"
#include "icons/music.h"
#include "icons/theater.h"

extern petipa::imgui::Resources res;
extern petipa::imgui::Context ctx;

petipa::imgui::Editor::Editor (const std::string& project_name_arg) :
	button_alert ("alert", 160,40),
	button_confirm ("confirm", 160,40),
	button_input ("input", 160,40),
	button_share ("share", 160,40),
	button_open_url ("open url", 160,40),
	button_exit ("exit", 160,40),
	button_visualization_options (60, 60, ICON(eye)),
	button_characters_dialog (60, 60, ICON(character)),
	button_music (60, 60, ICON(music)),
	button_stage (60, 60, ICON(theater)),
	button_notifications ("notifications", 240,40),
	button_about ("about", 240,40),
	project_name (project_name_arg)
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
	if (do_button (button_confirm))
		petipa::api::native::confirm ("Confirm", "Are you sure?");
	if (do_button (button_input)) {
		std::string text = petipa::api::native::text_input ("Please enter some text");
		if (!text.empty()) {
			std::string message = "You entered this text:\n";
			message += text;
			message += "\nThanks for your input.";
			petipa::api::native::alert ("Well done!", message);
		}
	}
	if (do_button (button_share))
		petipa::api::native::share_project (this->project_name); //TODO project path
	if (do_button (button_open_url))
		petipa::api::native::open_url ("https://petipa.dance/");
	if (do_button (button_exit))
		res.running = false;

	petipa::imgui::layout_start (Layout::Type::VERTICAL_DOWN_ALIGN_LEFT, 0, 0);
	if (do_button (button_visualization_options))
		petipa::api::native::open_visualization_options_dialog();
	if (do_button (button_characters_dialog))
		petipa::api::native::open_characters_dialog();
	if (do_button (button_music))
		petipa::api::native::open_music_dialog();
	if (do_button (button_stage))
		petipa::api::native::open_stage_dialog();
	if (do_button (button_notifications))
		petipa::api::native::open_notifications_dialog();
	if (do_button (button_about))
		petipa::api::native::open_about_dialog();

	void alert (const std::string& title, const std::string& text);
	bool confirm (const std::string& title, const std::string& text);
	std::string text_input (const std::string& title);
	void share_project (const std::string& file_path);
	void open_url (const std::string& url);
}

// vim600:foldmethod=syntax:foldnestmax=1:
