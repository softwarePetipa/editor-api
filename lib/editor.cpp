#include <string>
#include <unordered_map>
#include <petipa/api/editor.h>
#include "random.h"
namespace ed = petipa::api::editor;

static struct {
	ed::VisualizationOptions visualization_options;
	std::unordered_map<std::string, ed::Character> characters;
} project;

static void init()
{
	auto& op = project.visualization_options;
	op.show_path_parts = random_path_display_parts();
	op.path_line_width = random_double(ed::get_minimum_line_width(), ed::get_maximum_line_width());
	op.path_fade_time = random_double(ed::get_minimum_fade_time(), ed::get_maximum_fade_time());
	op.path_fade_opacity = random_double(0, 1);
	op.show_bar_markers = random_bool();
	op.show_complete_path = random_bool();
	op.show_grids_and_guides = random_bool();
	op.show_rulers = random_bool();
	op.show_evolutions = random_bool();
	op.character_display_type = random_character_display_type();
	op.show_characters_path = random_display_all();
	op.show_characters_name = random_display_all();
	op.show_tags_path = random_display_all();
	op.show_tags_label = random_display_all();

	ed::Character ch_array[] = {
		{ "Fulano",   "ff0000", "", {}, 1 },
		{ "Beltrano", "00ff00", "", {}, 1 },
		{ "Ciclano",  "0000ff", "", {}, 1 },
	};
	for (auto& ch : ch_array) {
		project.characters[ch.name] = ch;
	}
}

void ed::cancel_characters_and_tags_changes() {}

ed::VisualizationOptions ed::get_visualization_options()
{
	return project.visualization_options;
}

bool ed::set_visualization_options (const ed::VisualizationOptions&) { return false; }

void ed::cancel_visualization_options_changes() {}

std::vector<std::string> ed::get_character_list()
{
	std::vector<std::string> rc;
	for (const auto& e : project.characters)
		rc.push_back (e.first);
	return rc;
}

ed::Character ed::get_character (const std::string& name)
{
	return project.characters[name];
}

std::string ed::new_character()
{
	auto new_name;
	{// Find an unique character name.
		std::string base_name = "Anonymous";
		new_name = base_name;
		int n = 1;
		while (project.characters.exists(new_name)) {
			++n;
			std::stringstream ss;
			ss << base_name << " " << n;
			new_name = ss.str();
		}
	}

	// create a new character
	project.characters[new_name] = {
		new_name,
		petipa::ColorFactory::next().hex(),
		"",
		{},
		1
	};

	return new_name;
}

bool ed::delete_character (const std::string& name);
bool ed::rename_character (const std::string& old_name, const std::string& new_name);
bool ed::character_set_color (const std::string& name, const std::string& color);
bool ed::character_set_avatar (const std::string& name, const std::string& image_path);
bool ed::character_set_size (const std::string& name, double size);
bool ed::character_toggle_tag (const std::string& name, const std::string& label);
bool ed::character_set_name_display_flag (const std::string& name, bool);
bool ed::character_get_name_display_flag (const std::string& name);
bool ed::character_set_path_display_flag (const std::string& name, bool);
bool ed::character_get_path_display_flag (const std::string& name);

std::vector<std::string> ed::get_tag_list();
bool ed::rename_tag (const std::string& old_label, const std::string& new_name);
bool ed::new_tag (const std::string& label);
bool ed::delete_tag (const std::string& label);
bool ed::tag_set_label_display_flag (const std::string& label, bool);
bool ed::tag_get_label_display_flag (const std::string& label);
bool ed::tag_set_path_display_flag (const std::string& label, bool);
bool ed::tag_get_path_display_flag (const std::string& label);

ed::MusicDefinition ed::get_music_definition();
bool ed::music_preview_play (const std::string& music_title);
bool ed::music_preview_stop();
bool ed::set_music_file (const std::string& music_path);
bool ed::set_stock_music (const std::string& music_title);
bool ed::set_silence (unsigned int hours, unsigned int minutes, unsigned int seconds);

ed::Stage ed::get_stage_definition();
std::vector<ed::Stage> ed::get_stage_list();
bool ed::load_stage_image (const std::string* file_path);
bool ed::delete_stage_image (const std::string& file_path);
bool ed::set_stage_definition (const Stage&);
