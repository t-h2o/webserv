#include "File.hpp"

static int
test_a_file(const char *path_file, std::string expected_output)
{
	File file(path_file);

	std::string all_file;

	for (char c = file.getc(); c; c = file.getc())
		all_file += c;

	if (all_file != expected_output)
		return 1;
	return 0;
}

int
test_file_all_file(void)
{
	test_a_file("test/src/File/config.json", "{\"firstName\":\"John\"}");
	test_a_file("test/src/File/file.txt", "HelloWorld!IverylikeC++98......IMAO");

	return 0;
}
