#include "Stream.hpp"
#include "utils_json.hpp"
#include "setting.hpp"

int
test_json_check_config_normal(void)
{
	json::t_object *config;
	json::t_object *server_1;
	json::t_object *server_2;

	server_1 = new json::t_object; /* good values */
	server_2 = new json::t_object; /* wrong values */

	config = new json::t_object;

	(*server_1)["port"] = json::Value(new double(42));
	(*server_1)["path"] = json::Value(new std::string("/path/server1"));
	(*config)["server 1"] = json::Value(server_1);

	(*server_2)["port"] = json::Value(new double(82));
	(*server_2)["path"] = json::Value(new std::string("/path/server2"));
	(*config)["server 2"] = json::Value(server_2);

	(*config)["php-cgi"] = json::Value(new std::string(PATH_CGI_PHP));

	if (json::check_config(config))
	{
		delete config;
		return 1;
	}

	delete config;
	return 0;
}
