namespace petipa {
namespace api {
namespace native {

	// Methods that will be called by the Editor:

	void open_visualization_options_dialog();
	void open_characters_dialog (const std::string& character_name = "");
	void open_music_dialog();
	void open_stage_dialog();
	void open_notifications_dialog();
	void open_about_dialog();

	void alert (const std::string& title, const std::string& text);
	bool confirm (const std::string& title, const std::string& text);
	std::string text_input (const std::string& title);
	void share_project (const std::string& file_path);
	void open_url (const std::string& url);

}}}

#endif
