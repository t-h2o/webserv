#include "File.hpp"

int
test_file_get_string_empty_string(void)
{
	{
		//{"":"John"}
		json::File file("test/src/File/config_empty_string00.json");

		if (file.get_char() != '{')
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_string() != "")
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_next_char() != ':')
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_string() != "John")
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_next_char() != '}')
			return 1;
	}
	{
		//{"firstName":""}
		json::File file("test/src/File/config_empty_string01.json");

		if (file.get_char() != '{')
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_string() != "firstName")
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_next_char() != ':')
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_string() != "")
			return 1;

		if (file.get_next_char() != '"')
			return 1;

		if (file.get_next_char() != '}')
			return 1;
	}

	return 0;
}
