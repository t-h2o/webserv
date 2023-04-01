#include "File.hpp"

int
test_file(void)
{
	json::File file("test/src/File/file.txt");

	if (file.get_next_char() != 'H')
		return 1;

	return 0;
}
