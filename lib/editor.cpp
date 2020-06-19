#include <string>
#include <sstream>
#include <unordered_map>
#include <petipa/api/editor.h>
#include "random.h"
namespace ed = petipa::api::editor;

static struct
{
	ed::VisualizationOptions visualization_options;
	std::unordered_map<std::string, ed::Character> characters;
	std::vector<std::string> tags;
}
project;

void ed::init()
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

	project.tags = { "tag1", "tag2", "tag3" };
}

void ed::cancel_characters_and_tags_changes()
{
	//TODO: undo changes
}

ed::VisualizationOptions ed::get_visualization_options()
{
	return project.visualization_options;
}

bool ed::set_visualization_options (const ed::VisualizationOptions& op)
{
	project.visualization_options = op;
	return true; //TODO: check consistency?
}

void ed::cancel_visualization_options_changes()
{
	//TODO: undo changes
}

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

static bool has_character (const std::string& name)
{
	// Use .contains() when we switch to C++20
	return (project.characters.count(name) > 0);
}

std::string ed::new_character()
{
	std::string new_name;
	{// Find an unique character name.
		std::string base_name = "Anonymous";
		new_name = base_name;
		int n = 1;
		while (has_character (new_name)) {
			++n;
			std::stringstream ss;
			ss << base_name << " " << n;
			new_name = ss.str();
		}
	}

	// create a new character
	project.characters[new_name] = {
		new_name,
		"ff00ff", //TODO petipa::ColorFactory::next().hex(),
		"",
		{},
		1
	};

	return new_name;
}

bool ed::delete_character (const std::string& name)
{
	return (project.characters.erase (name) > 0);
}

bool ed::rename_character (const std::string& old_name, const std::string& new_name)
{
	if (has_character (old_name) && !has_character (new_name)) {
		auto character = project.characters[old_name];
		project.characters.erase (old_name);
		character.name = new_name;
		project.characters[new_name] = character;
		return true;
	}
	else
		return false;
}

bool ed::character_set_color (const std::string& name, const std::string& color)
{
	if (has_character (name)) {
		project.characters[name].color = color;
		return true;
	}
	else
		return false;
}

bool ed::character_set_avatar (const std::string& name, const std::string& image_path)
{
	if (has_character (name)) {
		project.characters[name].avatar_image_path = image_path;
		return true;
	}
	else
		return false;
}

bool ed::character_set_size (const std::string& name, double size)
{
	if (has_character (name)) {
		project.characters[name].size = size;
		return true;
	}
	else
		return false;
}

bool ed::character_toggle_tag (const std::string& name, const std::string& label)
{
	if (has_character (name)) {
		auto& tags = project.characters[name].tags;

		auto it = std::find (tags.begin(), tags.end(), label);
		if (it == tags.end())
			tags.push_back (label);
		else
			tags.erase (it);

		return true;
	}
	else
		return false;
}

bool ed::character_set_name_display_flag (const std::string& name, bool flag)
{
	if (has_character (name)) {
		project.characters[name].show_name = flag;
		return true;
	}
	else
		return false;
}

bool ed::character_get_name_display_flag (const std::string& name)
{
	if (has_character (name))
		return project.characters[name].show_name;
	else
		return false;
}

bool ed::character_set_path_display_flag (const std::string& name, bool flag)
{
	if (has_character (name)) {
		project.characters[name].show_path = flag;
		return true;
	}
	else
		return false;
}

bool ed::character_get_path_display_flag (const std::string& name)
{
	if (has_character (name))
		return project.characters[name].show_path;
	else
		return false;
}

std::vector<std::string> ed::get_tag_list()
{
	return project.tags;
}

static auto get_tag_itr (const std::string& label)
{
	return std::find (project.tags.begin(), project.tags.end(), label);
}

static bool has_tag (const std::string& label)
{
	return (get_tag_itr (label) != project.tags.end());
}

bool ed::rename_tag (const std::string& old_label, const std::string& new_label)
{
	auto itr = get_tag_itr (old_label);
	if (itr != project.tags.end()) {

		// Replace old_label by new_label on the tag list.
		project.tags.erase (itr);
		if (!new_label.empty())
			project.tags.push_back (new_label);

		// Rename tag for each character.
		for (const auto& character_pair : project.characters) {
			auto& tags = character_pair.second.tags;
			auto it = std::find (tags.begin(), tags.end(), old_label);
			if (it != tags.end()) {
				tags.erase (it);
				if (!new_label.empty())
					tags.push_back (new_label);
			}
		}

		return true;
	}
	else
		return false;
}

bool ed::new_tag (const std::string& label)
{
	if (!has_tag (label))
		project.tags.push_back (label);
	else
		return false;
}

bool ed::delete_tag (const std::string& label)
{
	return ed::rename_tag (label, "");
}

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

// vim600:fdm=syntax:fdn=1:
