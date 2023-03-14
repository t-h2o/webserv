#include "File.hpp"

int
test_file_all_file(void)
{
	File file("test/src/File/file.txt");

	std::string all_file;

	for (char c = file.getc(); c; c = file.getc())
		all_file += c;

	if (all_file != "Hello World !")
		return 1;

	return 0;
}
