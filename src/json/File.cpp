#include "File.hpp"

namespace json
{

File::File(const char *path_file) : _file(path_file, std::fstream::in), _index(0)
{
	/* Check if the file is valid */
	if (_file.is_open() == 0)
		throw std::runtime_error("Error: read(): file is not valid");

	getline(_file, _current_line);
}

File::~File(void) { _file.close(); }

char
File::get_char(void) const
{
	return _current_line[_index];
}

char
File::get_next_char(void)
{
	iter_to_next_char();
	return get_char();
}

/* "value to return"
 * ^            -> ^
 * move the index up to the next double quote
 */
std::string
File::get_string(void)
{
	size_t position_quote_start(_current_line.find_first_of('"', _index) + 1);
	size_t length(_current_line.find_first_of('"', _index + 1) - position_quote_start);
	_index += length + 1;

	return _current_line.substr(position_quote_start, length);
}

/* 1234
 * ^->^
 * move the index up to the last digit
 */
double
File::get_number(void)
{
	char  *end;
	double number(std::strtod(&(_current_line[_index]), &end));
	_index += end - &(_current_line[_index]) - 1;

	return number;
}

void
File::iter_to_next_char(void)
{
	++_index;
	while (!_file.eof())
	{
		if (_index == _current_line.size())
		{
			_index = 0;
			getline(_file, _current_line);
		}
		else if (isblank(_current_line[_index]))
			ignore_blank();
		else
			break;
	}
}

/* move the index up to the next no blank character
 * "last     next"
 *      ^ -> ^
 */
void
File::ignore_blank(void)
{
	while (_current_line[_index] && isblank(_current_line[_index]))
		++_index;
}

} /* namespace json */
