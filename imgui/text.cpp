#include "text.h"
#include "FontCache.h"
#include "../imgui/GL.h"

void petipa::imgui::render_text (petipa::imgui::FontCache* cache, double x, double y, double w, double h, const char* str)
{
	FontTexture ft = cache->get_texture (str);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ft.texture_id);
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glBegin(GL_QUADS);
		glTexCoord2f(0,0);  glVertex2d(x+0,    y+0);
		glTexCoord2f(1,0);  glVertex2d(x+ft.w, y+0);
		glTexCoord2f(1,1);  glVertex2d(x+ft.w, y+ft.h);
		glTexCoord2f(0,1);  glVertex2d(x+0,    y+ft.h);
	glEnd();

	glDisable(GL_TEXTURE_2D);
}
