#ifndef petipa_imgui_imgui_h_included
#define petipa_imgui_imgui_h_included

#include <string>
#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>

#define ICON(a) a##_png, a##_png_len

namespace petipa {
namespace imgui {

struct Layout
{//
	int x, y;
	int spacing = 10;
	enum class Type {
		HORIZONTAL_RIGHT_ALIGN_UP,
		HORIZONTAL_RIGHT_ALIGN_DOWN,
		HORIZONTAL_LEFT_ALIGN_UP,
		HORIZONTAL_LEFT_ALIGN_DOWN,
		VERTICAL_DOWN_ALIGN_LEFT,
		VERTICAL_DOWN_ALIGN_RIGHT,
		VERTICAL_UP_ALIGN_LEFT,
		VERTICAL_UP_ALIGN_RIGHT,
	} type;
};

struct Icon
{//
	unsigned char* data = nullptr;
	unsigned int data_len = 0;
	ALLEGRO_BITMAP* allegro_bitmap = nullptr;
	int width = 0, height = 0;
};

struct Button
{//
	Button (const std::string& label_, int w_, int h_)  : w(w_), h(h_), label (label_) { icons[0].data = nullptr; }
	Button (const std::string& label_)  : Button (label_, 0, 0) {}
	Button (int w_, int h_)  : Button ("", w_, h_) {}
	Button (int w_, int h_,
		unsigned char* data0, unsigned int data0_len,
		unsigned char* data1 = nullptr, unsigned int data1_len = 0,
		unsigned char* data2 = nullptr, unsigned int data2_len = 0);

	int state=0;
	int w, h;
	std::string label = "";
	Icon icons[3];
	bool tried_to_load_texture = false;
};

struct Context
{//
	bool running;
	bool redraw;
	int width, height;
	float dpi, hdpi, vdpi;
	int player_height;
	int win_x;
	int win_y;
	int ctrl_x;
	int ctrl_y;
	uint8_t mouse_buttons;
	bool hot = false;
	bool unfocus = false;
	double frame_interval = 0.01;
	float prompt_fade = 0;
	float prompt_target_fade = 0;
	struct { int i0, j0, i1, j1; } prompt_rect = { 0, 0, 0, 0 } ;
	Layout layout;
	Button* hot_button = nullptr;
	Button* active_button = nullptr;
#ifdef __APPLE__
	bool control_mod = false;
#endif
};

class Editor;

struct Resources
{//
	ALLEGRO_FONT* allegro_font = nullptr;
	ALLEGRO_TIMER* allegro_timer = nullptr;
	ALLEGRO_DISPLAY* allegro_display = nullptr;
	ALLEGRO_EVENT_QUEUE* allegro_queue = nullptr;
	Editor* editor = nullptr;
	bool init = false;
};

void loop_step();
void set_window_size (int, int);
void layout_start (Layout::Type, int x, int y);
bool do_button (Button&, int x, int y);
bool do_button (Button&);

}}
#endif

// vim600:fdm=marker:fmr={//,};:
