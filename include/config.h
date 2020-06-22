#ifndef petipa_api_config_h_included
#define petipa_api_config_h_included

namespace petipa {
namespace api {
namespace config {

	void load();
	void save();

	void toggle_dark_mode();
	bool get_dark_mode();

	void toggle_dashboard_alphabetic_sort();
	bool get_dashboard_alphabetic_sort();

	bool is_bottom_banner_visible();
	void hide_bottom_banner();
}}}

#endif
