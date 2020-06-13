#ifndef petipa_api_editor_h_included
#define petipa_api_editor_h_included

#include <string>
#include <vector>
#include <ctime>

namespace petipa {
namespace api {
namespace dashboard {

	bool is_bottom_banner_visible();
	void hide_bottom_banner();

	struct ProjectListSection {
		std::string label;
		std::vector<std::string> project_names;
	};
	std::vector<ProjectListSection> get_project_list_sections();

	bool open_new_project (void* system_context);
	bool open_project (const std::string& project_name, void* system_context);
	bool import_and_open_project (const std::string& file_path, void* system_context);
	bool copy_and_open_project (const std::string& project_name, void* system_context);
	bool rename_project (const std::string& old_name, const std::string& new_name);
	bool delete_project (const std::string& project_name);
	bool export_project (const std::string& project_name, const std::string& file_path);

	std::string get_project_file_extension();
	std::string get_new_name (const std::string& project_name);
	std::string project_name_to_file_name (const std::string& project_name);
	bool open_project_file (const std::string& file_path, void* system_context);

}}}

#endif
