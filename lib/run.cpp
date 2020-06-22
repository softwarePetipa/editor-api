#include <string>

static bool init_window (void* system_context)
{
	//TODO
	return false;
}

bool run_project (const std::string& project_name, void* system_context)
{
	if (!init_window (system_context))
		return false;

	bool running = true;
	while (running) {
		//TODO
		running = false;
	}

	return true;
}
