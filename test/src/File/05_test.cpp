#include "File.hpp"

int
test_file_get_number(void)
{
	//{"my number":1234}
	json::File file("test/src/File/number.json");

	if (file.get_char() != '{')
		return 1;

	if (file.get_next_char() != '"')
		return 1;

	if (file.get_string() != "my number")
		return 1;

	if (file.get_next_char() != '"')
		return 1;

	if (file.get_next_char() != ':')
		return 1;

	if (file.get_next_char() != '1')
		return 1;

	if (file.get_number() != 1234)
		return 1;

	if (file.get_char() != '4')
		return 1;

	if (file.get_next_char() != '}')
		return 1;

	if (file.get_next_char() != '\0')
		return 1;

	return 0;
}
