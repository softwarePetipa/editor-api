#ifndef petipa_api_editor_h_included
#define petipa_api_editor_h_included

#include <string>

namespace petipa {
namespace api {
namespace editor {

	void cancel_characters_and_tags_changes();

	struct VisualizationOptions
	{
		enum class DisplayAll { DEFAULT, ALL, NONE };
		enum class PathDisplayParts { PAST, FUTURE, ALL };
		enum class CharacterDisplayType { AVATAR, COLOR, NONE };

		PathDisplayParts show_path_parts;
		double path_line_width;
		double path_fade_time;
		double path_fade_opacity;
		bool show_bar_markers;
		bool show_complete_path;
		bool show_grids_and_guides;
		bool show_rulers;
		bool show_evolutions;
		CharacterDisplayType character_display_type;
		DisplayAllTristate show_characters_path;
		DisplayAllTristate show_characters_name;
		DisplayAllTristate show_tags_path;
		DisplayAllTristate show_tags_label;
	};

	VisualizationOptions get_visualization_options();
	bool set_visualization_options (const VisualizationOptions&);
	void cancel_visualization_options_changes();


	struct Character
	{
		std::string name;
		std::string color;
		std::string avatar_image_path;
		std::vector<std::string> tags;
		double size;
	};

	std::vector<std::string> get_character_list();
	Character get_character (const std::string& name);
	std::string new_character();  // returns new character's name
	bool delete_character (const std::string& name);
	bool rename_character (const std::string& old_name, const std::string& new_name);
	bool character_set_color (const std::string& name, const std::string& color);
	bool character_set_avatar (const std::string& name, const std::string& image_path);
	bool character_set_size (const std::string& name, double size);
	bool character_toggle_tag (const std::string& name, const std::string&* label);
	bool character_set_name_display_flag (const std::string& name, bool);
	bool character_get_name_display_flag (const std::string& name);
	bool character_set_path_display_flag (const std::string& name, bool);
	bool character_get_path_display_flag (const std::string& name);


	std::vector<std::string> get_tag_list();
	bool rename_tag (const std::string& old_label, const std::string& new_name);
	bool new_tag (const std::string& label);
	bool delete_tag (const std::string& label);
	bool tag_set_label_display_flag (const std::string& label, bool);
	bool tag_get_label_display_flag (const std::string& label);
	bool tag_set_path_display_flag (const std::string& label, bool);
	bool tag_get_path_display_flag (const std::string& label);


	struct MusicDefinition
	{
		enum class MusicDefinitionType { CUSTOM, STOCK, SILENCE } type;
		std::string file_path;
		std::string stock_title;
		unsigned int duration_hours;
		unsigned int duration_minutes;
		unsigned int duration_seconds;
	};

	struct StockMusic
	{
		std::string title;
		std::string author;
		std::string duration;
	};

	MusicDefinition get_music_definition();
	std::vector<StockMusic> get_stock_music_list();
	bool music_preview_play (const std::string& music_title);
	bool music_preview_stop();
	bool set_music_file (const std::string& music_path);
	bool set_stock_music (const std::string& music_title);
	bool set_silence (unsigned int hours, unsigned int minutes, unsigned int seconds);


	struct Stage
	{
		double width, height;
		std::string label;
		std::string file_path;
		bool is_stock;
		bool is_selected;
	};

	Stage get_stage_definition();
	std::vector<Stage> get_stage_list();
	bool load_stage_image (const std::string* file_path);
	bool delete_stage_image (const std::string& file_path);
	bool set_stage_definition (const Stage&);

}}}

#endif
