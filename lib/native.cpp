#include <iostream>
#include "../include/native.h"

void petipa::api::native::open_visualization_options_dialog()
{
	std::cout << "open visualization dialog\n";
}

void petipa::api::native::open_characters_dialog (const std::string& character_name)
{
	std::cout << "open characters dialog\n";
}

void petipa::api::native::open_music_dialog()
{
	std::cout << "open music dialog\n";
}

void petipa::api::native::open_stage_dialog()
{
	std::cout << "open stage dialog\n";
}

void petipa::api::native::open_notifications_dialog() {}
void petipa::api::native::open_about_dialog() {}

void petipa::api::native::alert (const std::string& title, const std::string& text)
{
	std::cout << "alert(" << title << ")(" << text << ")\n";
}

bool petipa::api::native::confirm (const std::string& title, const std::string& text)
{
	std::cout << "confirm(" << title << ")(" << text << ")\n";
	return false;
}

std::string petipa::api::native::text_input (const std::string& title)
{
	std::cout << "input(" << title << ")\n";
	return "";
}

void petipa::api::native::share_project (const std::string& file_path)
{
	std::cout << "share(" << file_path << ")\n";
}

void petipa::api::native::open_url (const std::string& url)
{
	std::cout << "open_url(" << url << ")\n";
}
