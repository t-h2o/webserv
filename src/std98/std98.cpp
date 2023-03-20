#include "std98.hpp"

namespace std98
{

std::string
to_string(double number)
{
	std::stringstream ss;

	ss << number;
	std::string s(ss.str());
	return s;
}

} /* namespace std98 */
