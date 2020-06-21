#include <string>
#include <sstream>
#include <unordered_map>
#include "../include/editor.h"
#include "../include/native.h"
#include "random.h"
#include "web.h"
#include "fs.h"
namespace ed = petipa::api::editor;

static struct
{
	ed::VisualizationOptions visualization_options;
	ed::MusicDefinition music_definition;
	std::vector<ed::Stage> stages;
	std::string selected_stage;

	std::unordered_map<std::string, ed::Character> characters;

	std::vector<std::string> tags;

	struct DisplayFlags { bool path, label; };
	std::unordered_map<std::string, DisplayFlags> tags_display_flags;
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

	project.music_definition = { ed::MusicDefinition::Type::SILENCE, "", "", 0, 5, 0 };
	project.stages = {
		{ 8, 5, "Rectangle", "rectangle.png", true, false },
		{ 8, 5, "Italian", "italian.png", true, true },
		{ 8, 5, "Hexagonal", "hexagonal.png", true, false },
		{ 8, 5, "Circle", "circle.png", true, false },
	};
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

static auto find (std::vector<std::string>& vec, const std::string& str)
{
	for (auto it = vec.begin();  it != vec.end();  ++it) {
		if (*it == str)
			return it;
	}

	return vec.end();
}

bool ed::character_toggle_tag (const std::string& name, const std::string& label)
{
	if (has_character (name)) {
		auto& tags = project.characters[name].tags;

		auto it = find (tags, label);
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

static bool has_tag (const std::string& label)
{
	return (find (project.tags, label) != project.tags.end());
}

bool ed::rename_tag (const std::string& old_label, const std::string& new_label)
{
	auto itr = find (project.tags, old_label);
	if (itr != project.tags.end()) {

		// Replace old_label by new_label on the tag list.
		project.tags.erase (itr);
		if (!new_label.empty())
			project.tags.push_back (new_label);

		// Rename tag for each character.
		for (auto& character_pair : project.characters) {
			auto& character_tags = character_pair.second.tags;
			auto it = find (character_tags, old_label);
			if (it != character_tags.end()) {
				character_tags.erase (it);
				if (!new_label.empty())
					character_tags.push_back (new_label);
			}
		}

		return true;
	}
	else
		return false;
}

bool ed::new_tag (const std::string& label)
{
	if (!has_tag (label)) {
		project.tags.push_back (label);
		return true;
	}
	else
		return false;
}

bool ed::delete_tag (const std::string& label)
{
	return ed::rename_tag (label, "");
}

static bool get_tag_display_flags (
		const std::string& label,
		const std::string& which)
{
	if (project.tags_display_flags.count (label) > 0) {
		const auto& flags = project.tags_display_flags[label];
		return which == "path" ? flags.path : flags.label;
	}
	else
		return false;
}

static bool set_tag_display_flags (
		const std::string& label,
		const std::string& which,
		bool value)
{
	if (has_tag (label)) {

		if (project.tags_display_flags.count (label) <= 0)
			project.tags_display_flags[label] = { false, false };

		if (which == "path")
			project.tags_display_flags[label].path = value;
		else
			project.tags_display_flags[label].label = value;

		return true;
	}
	else {
		return false;
	}
}

bool ed::tag_set_label_display_flag (const std::string& label, bool value)
{
	return set_tag_display_flags (label, "label", value);
}

bool ed::tag_get_label_display_flag (const std::string& label)
{
	return get_tag_display_flags (label, "label");
}

bool ed::tag_set_path_display_flag (const std::string& label, bool value)
{
	return set_tag_display_flags (label, "path", value);
}

bool ed::tag_get_path_display_flag (const std::string& label)
{
	return get_tag_display_flags (label, "path");
}


ed::MusicDefinition ed::get_music_definition()
{
	return project.music_definition;
}

bool ed::music_preview_play (const std::string& music_title)
{
	return true;
}

bool ed::music_preview_stop()
{
	return true;
}

bool ed::set_music_file (const std::string& music_path)
{
	auto& def = project.music_definition;
	def.type = ed::MusicDefinition::Type::CUSTOM;
	def.file_path = music_path;
	//TODO load music, set duration fields, validate
	return true;
}

bool ed::set_stock_music (const std::string& music_title)
{
	for (const auto& stock_music : petipa::api::web::get_stock_music_list()) {
		if (stock_music.title == music_title) {
			auto& def = project.music_definition;
			def.type = ed::MusicDefinition::Type::STOCK;
			def.file_path = petipa::api::web::download_stock_music (music_title, "." /*TODO*/);
			def.stock_title = music_title;
			def.duration_hours = stock_music.duration_hours;
			def.duration_minutes = stock_music.duration_minutes;
			def.duration_seconds = stock_music.duration_seconds;
			return true;
		}
	}

	return false;
}

bool ed::set_silence (unsigned int hours, unsigned int minutes, unsigned int seconds)
{
	auto& def = project.music_definition;
	def.type = ed::MusicDefinition::Type::SILENCE;
	def.file_path = "";
	def.stock_title = "";
	def.duration_hours = hours;
	def.duration_minutes = minutes;
	def.duration_seconds = seconds;
	return true; //TODO validate parameters
}

ed::Stage ed::get_stage_definition()
{
	for (const auto& s : project.stages) {
		if (s.is_selected)
			return s;
	}
	return {0,0,"","",false,false};
}

std::vector<ed::Stage> ed::get_stage_list()
{
	return project.stages;
}

bool stage_exists (const std::string& name)
{
	for (const auto& stage : project.stages) {
		if (stage.label == name)
			return true;
	}
	return false;
}

bool ed::load_stage_image (const std::string& file_path)
{
	//TODO check if valid image

	std::string name;
	{// get an unique name for the new stage

		fs::path path (file_path);
		std::string base_name = path.stem().string();
		name = base_name;
		unsigned n = 1;
		while (stage_exists (name)) {
			++n;
			std::stringstream ss;
			ss << base_name << " (" << n << ")";
			name = ss.str();
		}
	}

	//TODO copy image to data dir
	std::string copied_path = file_path;
	project.stages.push_back ({ 8, 5, name, copied_path, false, true });
	return true;
}

bool ed::delete_stage_image (const std::string& file_path)
{
	//TODO
	return false;
}

bool ed::set_stage_definition (const Stage& stage)
{
	if (stage.width <= 0 || stage.width <= 0) {
		petipa::api::native::alert ("Error", "Stage dimentions need to be positive.");
		return false;
	}

	bool found = false;
	for (auto& s : project.stages) {
#if 0 // compact
		found ||= s.is_selected = (s.label == stage.label);
#else // readable
		if (s.label == stage.label) {
			s.is_selected = true;
			found = true;
		}
		else {
			s.is_selected = false;
		}
#endif
	}

	if (found) {
		return true;
	}
	else {
		petipa::api::native::alert ("Error", "Something strange happened.");
		return false;
	}
}

// vim600:fdm=syntax:fdn=1:
