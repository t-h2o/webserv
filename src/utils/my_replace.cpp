#include "utils.hpp"

namespace utils
{

std::string
my_replace(std::string str, std::string find, std::string replace)
{
	for (int i = str.find(find); i != -1; i = str.find(find))
	{
		str.erase(i, find.length());
		str.insert(i, replace);
	}

	return str;
}

} /* namespace utils */