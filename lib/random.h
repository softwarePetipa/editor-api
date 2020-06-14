#ifndef petipa_mocklib_rng_h_included
#define petipa_mocklib_rng_h_included

#include <petipa/api/editor.h>
namespace ed = petipa::api::editor;
ed::VisualizationOptions::DisplayAll random_display_all();
ed::VisualizationOptions::PathDisplayParts random_path_display_parts();
ed::VisualizationOptions::CharacterDisplayType random_character_display_type();

double random_double (double from, double to);
int random_int (int from, int to);
bool random_bool();

#endif
