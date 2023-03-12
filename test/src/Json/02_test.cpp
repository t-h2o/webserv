#include "Stream.hpp"

#include "Json.hpp"

int
test_json_bad_path(void)
{
	Stream output;

	output.open();
	Value::t_object *config = read("bad_path");
	output.close();

	if (config != 0)
	{
		delete config;
		return 1;
	}

	if (output.check("", "Error: read(): file \"bad_path\" is not valid\n"))
		return 1;

	return 0;
}
