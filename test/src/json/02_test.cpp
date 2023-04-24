#include "utils_json.hpp"

int
test_json_bad_path(void)
{
	try
	{
		json::t_object *config = json::read("bad_path");
		(void)config;
	}
	catch (std::exception &e)
	{
		return 0;
	}

	return 1;
}
