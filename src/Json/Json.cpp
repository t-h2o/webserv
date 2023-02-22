#include "Json.hpp"

enum e_states
{
	WHITESPACE,
	OBJECT,
	STRING,
};

/* loop up to reach end of string or not a blank character */
void
Json::_loop_isblank(std::string const &line, size_t &index)
{
	while (line[index] && std::isblank(line[index]))
		++index;
}

/* process a line of the json */
void
Json::_process_line(std::string const &line)
{
	static bool states[3];
	size_t		index(0);

	while (line[index])
	{
		std::cout << line[index] << "\n";
		if (std::isblank(line[index]))
		{
			states[WHITESPACE] = 1;
			std::cout << "whitespace = " << states[WHITESPACE] << "\n";
			_loop_isblank(line, index);
		}
		else
		{
			if (line[index] == '{')
			{
				states[OBJECT] = 1;
				std::cout << "object = " << states[OBJECT] << "\n";
			}
			if (line[index] == '}')
			{
				states[OBJECT] = 0;
				std::cout << "object = " << states[OBJECT] << "\n";
			}
			if (line[index] == '"')
			{
				states[STRING] ^= 1;
				std::cout << "string = " << states[STRING] << "\n";
			}
			states[WHITESPACE] = 0;
			std::cout << "whitespace = " << states[WHITESPACE] << "\n";
			++index;
		}
	}
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
