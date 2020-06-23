#ifndef petipa_lib_util_h_included
#define petipa_lib_util_h_included

#include <string>
#include <sstream>
#include <algorithm>

namespace petipa {
namespace util {

template <typename T, typename F>
std::string get_new_name (const T& collection, const std::string& base_name, F get_element_name)
{
	//FIXME: "Noname (2)" should yield "Noname (3)", not "Noname (2) (2)".
	// Use regex to get current " (number)", and increment it.

	std::string new_name = base_name;
	int n = 1;
	while (find_if (collection.begin(), collection.end(),
				[&](const auto& element) {
					return (get_element_name (element) == new_name);
				}) != collection.end())
	{
		++n;
		std::stringstream ss;
		ss << base_name << " (" << n << ")";
		new_name = ss.str();
	}

	return new_name;
}

}}
#endif
