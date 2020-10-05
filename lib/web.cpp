#include <string>
#include <vector>
#include "../include/web.h"
namespace web = petipa::api::web;

bool web::login (const std::string& user_id, const std::string& password) { return true; }
bool web::saml_login (const std::string& provider) { return true; }
void web::logout() {}
std::string web::get_top_banner_content() { return ""; }
std::string web::get_bottom_banner_content() { return ""; }

std::vector<web::StockMusic> web::get_stock_music_list()
{
	std::vector<web::StockMusic> rc;
	rc.push_back ({ "Dom Quixote", "L. Minkus", "1:00", "1.5 Mb" });
	rc.push_back ({ "Lago dos Cisnes", "Tchaikovsky", "2:46", "2.7 Mb" });
	rc.push_back ({ "Copellia", "Leo Delibes", "4:45", "6.1 Mb" });
	rc.push_back ({ "Raymonda", "A. Glazunov", "3:39", "4.9 Mb"});
	return rc;
}

std::string download_stock_music (const std::string& title, const std::string& output_dir)
{
	return "";
}
