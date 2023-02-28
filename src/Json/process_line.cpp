#include "utils_json.hpp"

static void
print_line(std::string const &line, size_t index)
{
	std::cout << line << "\n";
	for (; index != 0; --index)
		std::cout << ' ';
	std::cout << '^' << std::endl;
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

		if (states[OBJECT] && states[STRING] && !states[KEY_FILLED] && !states[MIDDLE])
		{
			value.first = _get_string(line, index);
			states[KEY_FILLED] = 1;
		}
		else if (states[OBJECT] && states[STRING] && states[KEY_FILLED] && states[MIDDLE])
		{
			value.second = new Value(_get_string(line, index));
			config->insert_pair(value);
			states[KEY_FILLED] = 0;
		}
		else if (states[OBJECT] && !states[STRING] && states[KEY_FILLED] && !states[MIDDLE])
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
