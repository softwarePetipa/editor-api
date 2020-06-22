#include <ctime>
#include "../include/config.h"
namespace cfg = petipa::api::config;

static bool alpha_sort = false;
static bool dark_mode = false;
static std::time_t bottom_banner_close_time = 0;
static const std::time_t seconds_for_bottom_banner_to_reappear = 10; // 60*60*24*15; // 15 days

void cfg::load()
{
}

void cfg::save()
{
}

bool cfg::get_dashboard_alphabetic_sort()
{
	return alpha_sort;
}

void cfg::toggle_dashboard_alphabetic_sort()
{
	alpha_sort = !alpha_sort;
}

void cfg::toggle_dark_mode()
{
	dark_mode = !dark_mode;
}

bool cfg::get_dark_mode()
{
	return dark_mode;
}

bool cfg::is_bottom_banner_visible()
{
	std::time_t time_closed = bottom_banner_close_time - std::time(nullptr);
	return (time_closed >= seconds_for_bottom_banner_to_reappear);
}

void cfg::hide_bottom_banner()
{
	bottom_banner_close_time = std::time(nullptr);
}
