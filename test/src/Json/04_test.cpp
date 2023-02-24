#include "Stream.hpp"

#include "Config.hpp"
#include "Json.hpp"

static int
test_missing_brace(const char *path)
{
	Config *config;

	try
	{
		config = Json::read(path);
	}
	catch (const std::runtime_error &e)
	{
		return 0;
	}

	delete config;

	return 1;
}

int
test_json_missing_brace(void)
{
	if (test_missing_brace("test/src/Json/config_missing_brace00.json"))
		return 1;
	if (test_missing_brace("test/src/Json/config_missing_brace01.json"))
		return 1;
	return 0;
}
