#include "../include/config.h"

static bool alpha_sort = false;
static bool dark_mode = false;

void petipa::api::config::load()
{
}

void petipa::api::config::save()
{
}

bool petipa::api::config::get_dashboard_alphabetic_sort()
{
	return alpha_sort;
}

void petipa::api::config::toggle_dashboard_alphabetic_sort()
{
	alpha_sort = !alpha_sort;
}

void toggle_dark_mode()
{
	dark_mode = !dark_mode;
}

bool get_dark_mode()
{
	return dark_mode;
}
