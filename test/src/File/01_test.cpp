#include "File.hpp"

int
test_file(void)
{
	json::File file("test/src/File/file.txt");

	if (file.getc() != 'H')
		return 1;

	return 0;
}
