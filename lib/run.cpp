#include <string>
#include "../imgui/main.h"

bool run_project (const std::string& project_name, void* system_context)
{
	petipa::imgui::run (project_name, system_context);
	return true;
}
