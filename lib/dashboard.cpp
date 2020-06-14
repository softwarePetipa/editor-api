#include <string>
#include <vector>
#include <petipa/api/config.h>
#include <petipa/api/dashboard.h>
namespace db = petipa::api::dashboard;

std::string db::get_new_name (const std::string& project_name)
{
	return "new name";
}

bool db::open_project (const std::string& project_name, void* system_context) { return false; }
bool db::delete_project (const std::string& project_name) { return false; }
bool db::export_project (const std::string& project_name, const std::string& file_path) { return false; }
bool db::rename_project (const std::string& old_name, const std::string& new_name) { return false; }
bool db::open_new_project (void* system_context) { return false; }
bool db::open_project_file (const std::string& file_path, void* system_context) { return false; }
bool db::copy_and_open_project (const std::string& project_name, void* system_context) { return false; }
bool db::import_and_open_project (const std::string& file_path, void* system_context) { return false; }
bool db::is_bottom_banner_visible() { return false; }
void db::hide_bottom_banner() {}

std::vector<db::ProjectListSection> db::get_project_list_sections()
{
	std::vector<db::ProjectListSection> sections;
	if (petipa::api::config::get_dashboard_alphabetic_sort()) {
		db::ProjectListSection s1;
		s1.label = "todos";
		s1.project_names.push_back("projeto um");
		s1.project_names.push_back("projeto dois");
		s1.project_names.push_back("projeto tres");
		s1.project_names.push_back("projeto quatro");
		sections.push_back(s1);
	}
	else {
		db::ProjectListSection s1, s2;
		s1.label = "hoje";
		s1.project_names.push_back("projeto quatro");
		s1.project_names.push_back("projeto tres");
		s2.label = "ontem";
		s2.project_names.push_back("projeto dois");
		s2.project_names.push_back("projeto um");
		sections.push_back(s1);
		sections.push_back(s2);
	}
	return sections;
}

std::string db::project_name_to_file_name (const std::string& project_name)
{
	return "/some/file/name.petipa";
}

std::string db::get_project_file_extension()
{
	return "petipa";
}
