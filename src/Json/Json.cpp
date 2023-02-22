#include "Json.hpp"

void
Json::_process_line(std::string const &line)
{
	std::cout << line << std::endl;
}

void
Json::read(std::string const &path)
{
	std::fstream config;
	std::string	 line;

	config.open(path, std::fstream::in);
	getline(config, line);
	_process_line(line);
	config.close();
}
