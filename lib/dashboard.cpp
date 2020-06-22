#include <string>
#include <sstream>
#include <vector>
#include "../include/config.h"
#include "../include/dashboard.h"
#include "run.h"
namespace db = petipa::api::dashboard;

static std::vector<db::Project> projects = {
	{ "Um sonho", "há poucos minutos", "19:02" },
	{ "Dança de fim de ano", "anteontem", "8:40" },
	{ "Projeto pessoal", "10 de abril", "3:30" },
	{ "Mega espetáculo", "2018/04/30", "1:43:14" },
};

static bool has_project (const std::string& name)
{
	for (const auto& p : projects) {
		if (p.name == name)
			return true;
	}
	return false;
}

std::string db::get_new_name (const std::string& project_name)
{
	return "new name";
}

bool db::open_project (const std::string& project_name, void* system_context)
{
	return run_project (project_name, system_context);
}

bool db::delete_project (const std::string& project_name) { return false; }
bool db::export_project (const std::string& project_name, const std::string& file_path) { return false; }
bool db::rename_project (const std::string& old_name, const std::string& new_name) { return false; }

bool db::open_new_project (void* system_context)
{
	std::string new_name;
	{// Find an unique project name.
		std::string base_name = "Project";
		new_name = base_name;
		int n = 1;
		while (has_project (new_name)) {
			++n;
			std::stringstream ss;
			ss << base_name << " (" << n << ")";
			new_name = ss.str();
		}
	}

	return db::open_project (new_name, system_context);
}

bool db::open_project_file (const std::string& file_path, void* system_context)
{
	//TODO open project (to read the project name)
	//TODO check for duplicate project name
	//TODO copy project to data dir
	//TODO return db::open_project (project_name, system_context);
	return false;
}

bool db::copy_and_open_project (const std::string& project_name, void* system_context)
{
	//TODO
	return false;
}

bool db::import_and_open_project (const std::string& file_path, void* system_context)
{
	//TODO
	return false;
}

std::vector<db::ProjectListSection> db::get_project_list_sections()
{
	//TODO
	std::vector<db::ProjectListSection> sections;
	if (petipa::api::config::get_dashboard_alphabetic_sort()) {
		db::ProjectListSection s1;
		s1.label = "todos";
		s1.projects.push_back(projects[1]);
		s1.projects.push_back(projects[3]);
		s1.projects.push_back(projects[2]);
		s1.projects.push_back(projects[0]);
		sections.push_back(s1);
	}
	else {
		db::ProjectListSection s1, s2;
		s1.label = "hoje";
		s1.projects.push_back(projects[0]);
		s2.label = "última semana";
		s1.projects.push_back(projects[1]);
		s2.label = "outros";
		s2.projects.push_back(projects[2]);
		s2.projects.push_back(projects[3]);
	}
	return sections;
}

std::string db::project_name_to_file_name (const std::string& project_name)
{
	//TODO
	return "/some/file/name.petipa";
}

std::string db::get_project_file_extension()
{
	return "petipa";
}
