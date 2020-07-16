#ifndef petipa_imgui_text_h_included
#define petipa_imgui_text_h_included

#include "FontCache.h"

namespace petipa {
namespace imgui {

void render_text (FontCache*, double x, double y, double w, double h, const char*);

}}
#endif
