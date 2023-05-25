#include "Stream.hpp"
#include "utils_json.hpp"

int
test_json_check_config_bad_port(void)
{
	json::t_object *config;

	// the port shouldn't be a string
	{
		json::t_object *server_1;
		json::t_object *server_2;

		server_1 = new json::t_object; /* good values */
		server_2 = new json::t_object; /* wrong values */

		config = new json::t_object;

		(*server_1)["port"] = json::Value(new double(42));
		(*server_1)["path"] = json::Value(new std::string("/path/server1"));
		(*config)["server 1"] = json::Value(server_1);

		(*server_2)["port"] = json::Value(new std::string("I'm not a number"));
		(*server_2)["path"] = json::Value(new std::string("/path"));
		(*config)["server 2"] = json::Value(server_2);

		if (json::check_config(config) == 0)
		{
			delete config;
			return 1;
		}

		delete config;
		return 0;
	}

	// the port should exist
	{
		json::t_object *server_1;
		json::t_object *server_2;

		server_1 = new json::t_object; /* good values */
		server_2 = new json::t_object; /* wrong values */

		config = new json::t_object;

		(*server_1)["port"] = json::Value(new double(42));
		(*server_1)["path"] = json::Value(new std::string("/path/server1"));
		(*config)["server 1"] = json::Value(server_1);

		/* missing port */
		(*server_2)["path"] = json::Value(new std::string("/path"));
		(*config)["server 2"] = json::Value(server_2);

		if (json::check_config(config) == 0)
		{
			delete config;
			return 1;
		}

		delete config;
		return 0;
	}
}
