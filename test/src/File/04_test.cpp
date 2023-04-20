#include "File.hpp"

int
test_file_get_string(void)
{
	//{"firstName":"John"}
	json::File file("test/src/File/config.json");

	if (file.get_char() != '{')
		return 1;

	if (file.get_next_char() != '"')
		return 1;

	if (file.get_string() != "firstName")
		return 1;

	if (file.get_next_char() != '"')
		return 1;

	return 0;
}
