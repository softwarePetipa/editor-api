#include "imgui.h"
#include <SOIL2.h>
#include "text.h"
#include "../imgui/GL.h"

extern petipa::imgui::Resources res;
petipa::imgui::Context ctx;

void handle_sdl_events()
{
	SDL_Event event;
	while (SDL_PollEvent (&event)) {

		switch (event.type) {
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
					case SDL_WINDOWEVENT_RESIZED:
						petipa::imgui::set_window_size();
						break;
				}
				break;

			case SDL_MOUSEMOTION:
				ctx.win_x = ctx.ctrl_x = event.motion.x;
				ctx.win_y = ctx.ctrl_y = event.motion.y;
				ctx.hot_button = nullptr;
				break;

			case SDL_MOUSEBUTTONDOWN:
				ctx.mouse_buttons |= SDL_BUTTON(event.button.button);
				break;

			case SDL_MOUSEBUTTONUP:
				ctx.mouse_buttons &= ~SDL_BUTTON(event.button.button);
				break;

			case SDL_QUIT:
				res.running = false;
				break;

#ifdef __APPLE__
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				ctx.control_mod = (event.key.keysym.mod & KMOD_LCTRL);
				break;
#endif
			default:
				break;
		}
	}
}

void petipa::imgui::loop_step()
{
	static uint32_t last_tick = SDL_GetTicks();

	uint32_t current_tick = SDL_GetTicks();
	if (current_tick > last_tick) // also avoids wrap every 49 days
		ctx.frame_interval = (current_tick - last_tick)/1000.0;
	last_tick = current_tick;

	//FIXME retina hack
#ifdef __APPLE__
	double m = 2;
#else
	double m = 1;
#endif

	// If window is visible... //TODO: wait for show event
	if (SDL_GetWindowFlags (res.window) | SDL_WINDOW_SHOWN) {

		res.editor->update (ctx.frame_interval);

		glViewport (0, 0, m*res.width, m*res.height);
		glMatrixMode (GL_PROJECTION);

		// Render scene.
		glClear (GL_COLOR_BUFFER_BIT);
		res.editor->draw_frame();

		// Prepare to render UI elements.
		glViewport (0, 0, m*res.width, m*res.height);
		glLoadIdentity();
		gluOrtho2D (0, res.width, res.height, 0);

		if (!ctx.unfocus) {
			ctx.hot = false;
			res.editor->loop_step();
		}

		// Present new frame.
		SDL_GL_SwapWindow (res.window);
	}

	handle_sdl_events();
}

void petipa::imgui::set_window_size()
{
	SDL_GetWindowSize (res.window, &res.width, &res.height);
	ctx.player_height = res.height/8;
	if (SDL_GetDisplayDPI (
				SDL_GetWindowDisplayIndex (res.window),
				&res.dpi,
				&res.hdpi,
				&res.vdpi
		) != 0)
	{
		fprintf (stderr, "Couldn't get display DPI: %s\n", SDL_GetError());
	}

	res.editor->resize();
}

petipa::imgui::Button::Button (int w_, int h_,
		unsigned char* data0, unsigned int data0_len,
		unsigned char* data1, unsigned int data1_len,
		unsigned char* data2, unsigned int data2_len) : w(w_), h(h_)
{
	icons[0].data = data0;  icons[0].data_len = data0_len;
	icons[1].data = data1;  icons[1].data_len = data1_len;
	icons[2].data = data2;  icons[2].data_len = data2_len;
}

static void render_button (petipa::imgui::Button& b, int x, int y)
{
	float alpha = (ctx.active_button == &b) ? 1 : (ctx.hot_button == &b) ? .8 : .6;
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (b.icons[0].data) { // has textures

		if (!b.tried_to_load_texture) {
			// load textures
			for (int i = 0; b.icons[i].data; ++i)
				b.icons[i].texture_id = SOIL_load_OGL_texture_from_memory(
						b.icons[i].data,
						b.icons[i].data_len,
						SOIL_LOAD_AUTO,
						SOIL_CREATE_NEW_ID,
						SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
						//SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT
				);
			b.tried_to_load_texture = true;
		}

		// apply texture
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, b.icons[b.state].texture_id);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glColor4f (1, 1, 1, alpha);
	}
	else { // no textures

		float state_colors[][3] = { {1.,1.,1.}, {0x77/255.,0x66/255.,1.}, {.4,.4,1.}, {1.,.4,.4} };
		float* color = state_colors[b.state];
		glColor4f (color[0], color[1], color[2], alpha);
	}

	// draw rectangle
	glBegin(GL_POLYGON);
		glTexCoord2f(0, 0);  glVertex2f(x, y);
		glTexCoord2f(1, 0);  glVertex2f(x+b.w-1, y);
		glTexCoord2f(1, 1);  glVertex2f(x+b.w-1, y+b.h-1);
		glTexCoord2f(0, 1);  glVertex2f(x, y+b.h-1);
	glEnd();

	// finalize OpenGL state
	glDisable(GL_BLEND);
	if (b.icons[0].data)
		glDisable(GL_TEXTURE_2D);

	// draw text label
	if (!b.label.empty()) {
		glColor4f (0, 0, 0, 1);
		petipa::imgui::render_text (res.font_cache, x+4, y+4, b.w-8, b.h-8, b.label.c_str());
	}
}

bool petipa::imgui::do_button (petipa::imgui::Button& b, int x, int y)
{
	bool result = false;

	if (!ctx.mouse_buttons) {
		if (ctx.win_x >= x && ctx.win_x < x+b.w && ctx.win_y >= y && ctx.win_y < y+b.h) {
			ctx.hot_button = &b;
			ctx.hot = true;
		}
	}

	if (ctx.active_button == &b) {
		if (!ctx.mouse_buttons) {
			if (ctx.hot_button == &b)
				result = true;
			ctx.active_button = nullptr;
		}
	}
	else if (ctx.hot_button == &b) {
		if (ctx.mouse_buttons)
			ctx.active_button = &b;
	}

	render_button (b, x, y);

	return result;
}

bool petipa::imgui::do_button (petipa::imgui::Button& b)
{
	int x = ctx.layout.x;
	int y = ctx.layout.y;
	switch (ctx.layout.type) {
		using petipa::imgui::Layout;
		case Layout::Type::HORIZONTAL_RIGHT_ALIGN_UP:
			x += ctx.layout.spacing;
			y += ctx.layout.spacing;
			ctx.layout.x += ctx.layout.spacing + b.w;
			break;
		case Layout::Type::HORIZONTAL_RIGHT_ALIGN_DOWN:
			x += ctx.layout.spacing;
			y -= ctx.layout.spacing + b.h;
			ctx.layout.x += ctx.layout.spacing + b.w;
			break;
		case Layout::Type::HORIZONTAL_LEFT_ALIGN_UP:
			x -= ctx.layout.spacing + b.w;
			y += ctx.layout.spacing;
			ctx.layout.x -= ctx.layout.spacing + b.w;
			break;
		case Layout::Type::HORIZONTAL_LEFT_ALIGN_DOWN:
			x -= ctx.layout.spacing + b.w;
			y -= ctx.layout.spacing + b.h;
			ctx.layout.x -= ctx.layout.spacing + b.w;
			break;
		case Layout::Type::VERTICAL_DOWN_ALIGN_LEFT:
			x += ctx.layout.spacing;
			y += ctx.layout.spacing;
			ctx.layout.y += ctx.layout.spacing + b.h;
			break;
		case Layout::Type::VERTICAL_DOWN_ALIGN_RIGHT:
			x -= ctx.layout.spacing + b.w;
			y += ctx.layout.spacing;
			ctx.layout.y += ctx.layout.spacing + b.h;
			break;
		case Layout::Type::VERTICAL_UP_ALIGN_LEFT:
			x += ctx.layout.spacing;
			y -= ctx.layout.spacing + b.h;
			ctx.layout.y -= ctx.layout.spacing + b.h;
			break;
		case Layout::Type::VERTICAL_UP_ALIGN_RIGHT:
			x -= ctx.layout.spacing + b.w;
			y -= ctx.layout.spacing + b.h;
			ctx.layout.y -= ctx.layout.spacing + b.h;
			break;
	}

	return petipa::imgui::do_button (b, x, y);
}

void petipa::imgui::layout_start (petipa::imgui::Layout::Type type, int x, int y)
{
	ctx.layout.spacing = 10;
	ctx.layout.x = x;
	ctx.layout.y = y;
	ctx.layout.type = type;
}

// vim600:foldmethod=syntax:foldnestmax=1:
