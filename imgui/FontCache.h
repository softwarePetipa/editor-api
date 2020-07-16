#ifndef petipa_imgui_FontCache_h_included
#define petipa_imgui_FontCache_h_included

#include <string>
#include <unordered_map>
#include <SDL_ttf.h>

namespace petipa {
namespace imgui {

struct FontTexture
{
	FontTexture (unsigned int a, unsigned long b, int c, int d) :
		texture_id (a),
		access_idx (b),
		w (c),
		h (d)
	{}

	unsigned int texture_id;
	unsigned long access_idx;
	int w, h;
};

class FontCache
{
public:
	FontCache();
	FontTexture get_texture (const std::string&);
	void garbage_collector();

private:
	TTF_Font* font;
	std::unordered_map < std::string, FontTexture > texture_map;
	unsigned long access_count = 0;
};

}}
#endif
