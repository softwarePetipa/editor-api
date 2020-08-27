#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "main.h"
#include "imgui.h"
#include "Editor.h"

#define MY_WINDOW_WIDTH   800
#define MY_WINDOW_HEIGHT  600

petipa::imgui::Resources res;
petipa::imgui::Context ctx;

static bool init_allegro()
{
	if (!res.init) {
		res.init = true;

		al_init();
		al_init_primitives_addon();
		if (!al_is_image_addon_initialized())
			al_init_image_addon();
		al_install_keyboard();
		al_install_mouse();
	}

	if (res.allegro_display == nullptr) {
		res.allegro_display = al_create_display(MY_WINDOW_WIDTH, MY_WINDOW_HEIGHT);
		ALLEGRO_ASSERT (res.allegro_display != nullptr);
	}

	if (res.allegro_queue == nullptr) {
		res.allegro_queue = al_create_event_queue();
		ALLEGRO_ASSERT (res.allegro_queue != nullptr);

		al_register_event_source (res.allegro_queue, al_get_keyboard_event_source());
		al_register_event_source (res.allegro_queue, al_get_mouse_event_source());
		al_register_event_source (res.allegro_queue, al_get_display_event_source (res.allegro_display));
		al_register_event_source (res.allegro_queue, al_get_timer_event_source (res.allegro_timer));
	}

	if (res.allegro_font == nullptr) {
		res.allegro_font = al_create_builtin_font();
		ALLEGRO_ASSERT (res.allegro_font != nullptr);
	}

	if (res.allegro_timer == nullptr) {
		res.allegro_timer = al_create_timer (1.0 / 30.0);
		ALLEGRO_ASSERT (res.allegro_timer != nullptr);
	}

	petipa::imgui::set_window_size (
			al_get_display_width  (res.allegro_display),
			al_get_display_height (res.allegro_display));
	ctx.running = true;

	return true;
}

bool petipa::imgui::run (const std::string& project_name, void*)
{
	res.editor = new petipa::imgui::Editor (project_name);

	if (!init_allegro())
		return false;

	while (ctx.running) {
		petipa::imgui::loop_step();
	}

	al_destroy_font (res.allegro_font);
	res.allegro_font = nullptr;

	al_destroy_event_queue (res.allegro_queue);
	res.allegro_queue = nullptr;

	al_destroy_display (res.allegro_display);
	res.allegro_display = nullptr;

	delete res.editor;
	res.editor = nullptr;

	return true;
}

// vim600:foldmethod=syntax:foldnestmax=1:
