#include <string>
#include "../imgui/main.h"

bool run_project (const std::string& project_name, void* system_context)
{
	petipa::imgui::run (system_context);
	return true;
}
