#ifndef petipa_lib_util_h_included
#define petipa_lib_util_h_included

#include <string>
#include <vector>
#include <sstream>

namespace petipa {
namespace util {

template <typename T, typename F>
bool collection_has_name (const T& collection, const std::string& name, F get_element_name)
{
	for (const auto& element : collection) {
		if (get_element_name (element) == name)
			return true;
	}
	return false;
}

template <typename T, typename F>
std::string get_new_name (const T& collection, const std::string& base_name, F get_element_name)
{
	std::string new_name = base_name;
	int n = 1;
	while (collection_has_name (collection, new_name, get_element_name)) {
		++n;
		std::stringstream ss;
		ss << base_name << " (" << n << ")";
		new_name = ss.str();
	}

	return new_name;
}

}}
#endif
