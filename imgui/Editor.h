#ifndef petipa_imgui_Editor_h_included
#define petipa_imgui_Editor_h_included

#include <string>
#include "imgui.h"

namespace petipa {
namespace imgui {

class Editor
{
public:
	Editor (const std::string&);
	~Editor();
	void draw_frame() {}
	void loop_step();
	void update (double) {}
	void resize() {}

private:
	void handle_mouse_move();

	Button button_alert;
	Button button_confirm;
	Button button_input;
	Button button_share;
	Button button_open_url;
	Button button_exit;

	Button button_visualization_options;
	Button button_characters_dialog;
	Button button_music;
	Button button_stage;
	Button button_notifications;
	Button button_about;

	std::string project_name;
};

}}
#endif
