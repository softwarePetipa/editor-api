#include <SDL.h>

#include "main.h"
#include "imgui.h"

#define MY_WINDOW_WIDTH   800
#define MY_WINDOW_HEIGHT  600

petipa::imgui::Resources res;

static bool init_sdl()
{
	static bool init = false;
	if (!init) {
		init = true;
		if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
			fprintf (stderr, "SDL_Init: %s\n", SDL_GetError());
			exit (1);
		}
		atexit(SDL_Quit);
	}

	res.window = SDL_CreateWindow (
			"Petipa", // petipa::global::window_title().c_str(),
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			MY_WINDOW_WIDTH, MY_WINDOW_HEIGHT,
			SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_UTILITY
	);
	if (res.window == NULL) {
		fprintf (stderr, "SDL_CreateWindow: %s\n", SDL_GetError());
		return false;
	}

	res.gl_context = SDL_GL_CreateContext (res.window);
	SDL_GL_SetSwapInterval (1);

	petipa::imgui::set_window_size();
	res.running = true;
	return true;
}

bool petipa::imgui::run (const std::string& project_name, void*)
{
	res.editor = new petipa::imgui::Editor (project_name);
	res.font_cache = new petipa::imgui::FontCache();

	if (!init_sdl())
		return false;

	while (res.running) {
		petipa::imgui::loop_step();
	}

	SDL_DestroyWindow (res.window);
	res.window = nullptr;

	delete res.editor;
	res.editor = nullptr;

	delete res.font_cache;
	res.font_cache = nullptr;

	return true;
}

// vim600:foldmethod=syntax:foldnestmax=1:
