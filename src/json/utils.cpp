#include "utils_json.hpp"

namespace json
{

/* get the string value up to the next '"'
 * "the value"
 * ^      -> ^
 */
std::string
_get_string(std::string const &line, size_t &index)
{
	std::string value;

	if (line[index] == '"')
		++index;
	while (line[index] && line[index] != '"')
		value += line[index++];

	--index;

	if (value == "")
		throw std::runtime_error("Json: _get_string(): empty string");

	return value;
}

} /* namespace json */
