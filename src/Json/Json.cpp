#include "Json.hpp"

/* loop up to reach end of string or not a blank character */
void
Json::_loop_isblank(std::string const &line, size_t &index)
{
	while (line[index] && std::isblank(line[index]))
		++index;
}

void
Json::_process_line(std::string const &line)
{
	size_t index(0);

	while (line[index])
		std::cout << line[index++];
}

void
Json::read(std::string const &path)
{
	std::fstream config;
	std::string	 line;

	config.open(path, std::fstream::in);

	/* Read each lines up to EOF */
	for (getline(config, line); !config.eof(); getline(config, line))
		_process_line(line);
	std::cout << std::endl;

	config.close();
}
