#include "Stream.hpp"

#include "utils_json.hpp"

static int
test_missing_brace(const char *path)
{
	json::t_object *config;

	config = json::read(path);
	if (config)
		return 1;
	return 0;
}

int
test_json_missing_brace(void)
{
	if (test_missing_brace("test/src/json/config_missing_brace00.json"))
		return 1;
	if (test_missing_brace("test/src/json/config_missing_brace01.json"))
		return 1;
	return 0;
}
