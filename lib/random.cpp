#include <random>
#include <petipa/api/editor.h>
namespace ed = petipa::api::editor;

static std::random_device rd;
static std::mt19937 gen(rd());

double random_double (double from, double to)
{
	std::uniform_real_distribution<> dist (from, to);
	return dist(gen);
}

int random_int (int from, int to)
{
	std::uniform_int_distribution<> dist (from, to);
	return dist(gen);
}

bool random_bool()
{
	std::uniform_int_distribution<> dist (0, 1);
	return (dist(gen) == 1);
}

ed::VisualizationOptions::PathDisplayParts random_path_display_parts()
{
	int rnd = random_int(1,3);
	return
		rnd==1 ? ed::VisualizationOptions::PathDisplayParts::PAST :
		rnd==2 ? ed::VisualizationOptions::PathDisplayParts::FUTURE :
		ed::VisualizationOptions::PathDisplayParts::ALL;
}

ed::VisualizationOptions::CharacterDisplayType random_character_display_type()
{
	int rnd = random_int(1,3);
	return
		rnd==1 ? ed::VisualizationOptions::CharacterDisplayType::AVATAR :
		rnd==2 ? ed::VisualizationOptions::CharacterDisplayType::COLOR :
		ed::VisualizationOptions::CharacterDisplayType::NONE;
}

ed::VisualizationOptions::DisplayAll random_display_all()
{
	int rnd = random_int(1,3);
	return
		rnd==1 ? ed::VisualizationOptions::DisplayAll::DEFAULT :
		rnd==2 ? ed::VisualizationOptions::DisplayAll::ALL :
		ed::VisualizationOptions::DisplayAll::NONE;
}
