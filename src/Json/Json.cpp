#include "Json.hpp"

void
Json::read(std::string const &path)
{
	std::fstream config;
	std::string	 line;

	config.open(path, std::fstream::in);
	getline(config, line);
	std::cout << line << std::endl;
}
