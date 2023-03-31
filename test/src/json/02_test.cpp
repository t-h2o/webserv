#include "Stream.hpp"

#include "utils_json.hpp"

int
test_json_bad_path(void)
{
	Stream output;

	output.open();
	json::t_object *config = json::read("bad_path");
	output.close();

	if (config != 0)
	{
		delete config;
		return 1;
	}

	if (output.check("", "Error: json::read(): file \"bad_path\" is not valid\n"))
		return 1;

	return 0;
}
