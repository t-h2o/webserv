#include "utils_json.hpp"

/* get the string value up to the next '"'
 * "the value"
 * ^     -> ^
 */

static void
print_line(std::string const &line, size_t index)
{
	std::cout << line << "\n";
	for (; index != 0; --index)
		std::cout << ' ';
	std::cout << '^' << std::endl;
}
std::string
_get_string(std::string const &line, size_t &index)
{
	std::string value;

	if (line[index] == '"')
		++index;
	while (line[index] && line[index] != '"')
		value += line[index++];

	--index;

	if (value == "")
		throw std::runtime_error("Json: _get_string():\n" + line + "\nempty string");

	return value;
}

/* move the index up to the next no blank character
 * "last     next"
 *      ^ -> ^
 */
static void
_ignore_blank(std::string const &line, size_t &index)
{
	while (line[index] && isblank(line[index]))
		++index;
}

static void
_set_states(char character, bool states[NSTATES])
{
	if (character == '{')
	{
		states[OBJECT] = 1;
	}
	else if (character == '}')
	{
		if (states[OBJECT] == 0)
			throw std::runtime_error("Json: object didn't start by a '{'");
		states[OBJECT] = 0;
	}
	else if (character == '"')
	{
		states[STRING] ^= 1;
	}
	else if (character == ':')
	{
		states[MIDDLE] = 1;
	}
}

static void
_print_case(std::string const &line, size_t index, bool states[NSTATES], bool show_states)
{
	if (!show_states)
		print_line(line, index);
	else
		std::cout << "Undefined case\n"
				  << states[OBJECT] << " OBJECT\n"
				  << states[STRING] << " STRING\n"
				  << states[KEY_FILLED] << " KEY_FILLED\n"
				  << states[MIDDLE] << " MIDDLE\n"
				  << std::endl;
}

/* process a line of the json */
void
_process_line(Config *config, std::string const &line, bool states[NSTATES])
{
	size_t							index(0);
	std::pair<std::string, Value *> value;

	_ignore_blank(line, index);
	while (line[index])
	{
		_set_states(line[index], states);
		_print_case(line, index, states, false);

		if (states[STRING] && states[KEY_FILLED] == 0)
		{
			value.first = _get_string(line, index);
			states[KEY_FILLED] = 1;
		}
		else if (states[STRING] && states[KEY_FILLED])
		{
			value.second = new Value(_get_string(line, index));
			config->insert_pair(value);
			states[KEY_FILLED] = 0;
		}
		else if (states[OBJECT] && states[STRING] == 0 && states[KEY_FILLED] && states[MIDDLE] == 0)
		{
		}
		else if (states[OBJECT] && !states[STRING] && !states[KEY_FILLED] && !states[MIDDLE])
		{
		}
		else if (!states[OBJECT] && !states[STRING] && !states[KEY_FILLED] && states[MIDDLE])
		{
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && states[MIDDLE])
		{
		}
		else if (states[OBJECT] && !states[STRING] && !states[KEY_FILLED] && states[MIDDLE])
		{
		}
		else
		{
			_print_case(line, index, states, true);
		}
		++index;
		_ignore_blank(line, index);
	}
}

Config *
read(char const *path)
{
	bool		 states[NSTATES];
	Config		*config;
	std::fstream file;
	std::string	 line;

	memset(states, 0, sizeof(bool) * NSTATES);
	file.open(path, std::fstream::in);

	/* Check if the file is valid */
	if (file.is_open() == 0)
	{
		std::cerr << "Error: read(): file \"" << path << "\" is not valid" << std::endl;
		return 0;
	}

	config = new Config;

	/* Read each lines up to EOF */
	for (getline(file, line); !file.eof(); getline(file, line))
		_process_line(config, line, states);

	if (states[OBJECT])
		throw std::runtime_error("Json: object not finished by a '}'");

	file.close();

	return config;
}
