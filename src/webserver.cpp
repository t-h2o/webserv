#include "Json.hpp"
#include "cgi.hpp"
#include "cluster.hpp"
#include <iostream>

int
webserver(const char *path_config_file)
{
	std::cout << "Web server written in C++98" << std::endl;

	json::t_object *config(0);

	if (json::load_config(path_config_file, &config))
	{
		delete config;
		return 1;
	}

	CGI::set_php_binary(config->at("php-cgi").get<std::string>());

	Cluster cluster;
	cluster.load_cluster(config);
	cluster.setup();
	cluster.run();

	return 0;
}
