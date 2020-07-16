#include "FontCache.h"
#include <cassert>
#include <SDL_ttf.h>
#include <SOIL2.h>

petipa::imgui::FontCache::FontCache()
{
	static bool init = false;
	if (!init) {
		init = true;
		auto ttf_init_rc = TTF_Init();
		assert (ttf_init_rc >= 0);
		atexit (TTF_Quit);
	}

	font = TTF_OpenFont ("font.ttf", 24);
	if (!font) {
		fprintf (stderr,  "Error opening font.ttf: %s\n", TTF_GetError());
		exit (2);
	}
}

petipa::imgui::FontTexture petipa::imgui::FontCache::get_texture (const std::string& str)
{
	auto itr = texture_map.find (str);

	if (itr != texture_map.end()) { // Found cached texture.
		itr->second.access_idx = ++access_count;
		return itr->second;
	}
	else { // No cached texture found.

		// Create new texture.
		SDL_Color color = { 0xff, 0xff, 0xff, 0xff };
		SDL_Surface* surf = TTF_RenderUTF8_Blended (font, str.c_str(), color);
		assert (surf != nullptr);  //TODO: proper error handling
		int tex_w = surf->w, tex_h = surf->h;
		unsigned int texture_id = SOIL_create_OGL_texture (
				(const unsigned char*) surf->pixels,
				&tex_w, &tex_h, surf->format->BytesPerPixel,
				0,
				SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		SDL_FreeSurface (surf);

		// Save new texture on the cache map, and return it.
		return texture_map.emplace (
				str,
				FontTexture (texture_id, ++access_count, surf->w, surf->h)
		).first->second;
	}
}

void petipa::imgui::FontCache::garbage_collector()
{
	//TODO: discard old textures
	//glDeleteTextures(1, &ft.texture_id);
}
