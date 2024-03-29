#include "File.hpp"

static int
test_a_file(const char *path_file, std::string expected_output)
{
	json::File file(path_file);

	std::string all_file;

	for (char c = file.get_next_char(); c; c = file.get_next_char())
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
