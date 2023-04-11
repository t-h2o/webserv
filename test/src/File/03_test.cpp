#include "File.hpp"

int
test_file_not_valid_file(void)
{
	try
	{
		json::File file("not_valid.not_valid");
	}
	catch (std::exception &e)
	{
		return 0;
	}

	return 1;
}
