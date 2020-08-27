#include "imgui.h"
#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_memfile.h>
#include "Editor.h"

extern petipa::imgui::Resources res;
extern petipa::imgui::Context ctx;

void handle_allegro_events()
{
	ALLEGRO_EVENT event;
	al_wait_for_event (res.allegro_queue, &event);

	switch (event.type) {
		case ALLEGRO_EVENT_TIMER:
			ctx.redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			switch (event.keyboard.keycode) {
				case ALLEGRO_KEY_C:
					break;
				case ALLEGRO_KEY_UP:
					break;
				case ALLEGRO_KEY_DOWN:
					break;
				case ALLEGRO_KEY_Q:
				case ALLEGRO_KEY_ESCAPE:
					ctx.running = false;
					break;
				default:
					break;
			}
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			ctx.running = false;
			break;
		case ALLEGRO_EVENT_DISPLAY_RESIZE:
			petipa::imgui::set_window_size (event.display.width, event.display.height);
			ctx.redraw = true;
			break;
		case ALLEGRO_EVENT_MOUSE_AXES:
			ctx.win_x = ctx.ctrl_x = event.mouse.x;
			ctx.win_y = ctx.ctrl_y = event.mouse.y;
			ctx.hot_button = nullptr;
			break;
#define BUTTON(X) (1 << ((X)-1))
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			ctx.mouse_buttons |= BUTTON(event.mouse.button);
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
			ctx.mouse_buttons &= ~BUTTON(event.mouse.button);
			break;
#undef BUTTON
		default:
			break;
	}
}

void petipa::imgui::loop_step()
{
	handle_allegro_events();

	if (ctx.redraw && al_is_event_queue_empty (res.allegro_queue))
	{
		static double last_tick = al_get_time();

		double current_tick = al_get_time();
		if (current_tick > last_tick) // also avoids wrap every 49 days
			ctx.frame_interval = (current_tick - last_tick);
		last_tick = current_tick;

		if (!ctx.unfocus) {
			ctx.hot = false;
			res.editor->loop_step();
		}
		res.editor->update (ctx.frame_interval);
		res.editor->draw_frame();
		al_flip_display();
		ctx.redraw = false;
	}
}

void petipa::imgui::set_window_size (int width, int height)
{
	ctx.width  = width;
	ctx.height = height;
	ctx.player_height = ctx.height/8;
	ctx.dpi = ctx.hdpi = ctx.vdpi = al_get_monitor_dpi (ALLEGRO_DEFAULT_DISPLAY_ADAPTER);
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

	if (b.icons[0].data) { // has bitmaps

		if (!b.tried_to_load_texture) {
			// load bitmaps
			for (int i = 0; b.icons[i].data; ++i) {
				ALLEGRO_FILE* file = al_open_memfile (b.icons[i].data, b.icons[i].data_len, "r");
				ALLEGRO_ASSERT (file != nullptr);
				b.icons[i].allegro_bitmap = al_load_bitmap_f (file, ".png");
				b.icons[i].width  = al_get_bitmap_width  (b.icons[i].allegro_bitmap);
				b.icons[i].height = al_get_bitmap_height (b.icons[i].allegro_bitmap);
				al_fclose (file);
			}
			b.tried_to_load_texture = true;
		}

		auto& icon = b.icons[b.state];
		al_draw_scaled_bitmap (icon.allegro_bitmap,
				0, 0, icon.width, icon.height,
				x, y, b.w, b.h,
				0);
	}
	/*
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
	*/
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
