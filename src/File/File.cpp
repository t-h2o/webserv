#include "File.hpp"

File::File(const char *path_file) : _index(0)
{
	_file.open(path_file, std::fstream::in);

	/* Check if the file is valid */
	if (_file.is_open() == 0)
		throw std::runtime_error("Error: read(): file is not valid");

	getline(_file, _current_line);
}

File::~File(void) { _file.close(); }

char
File::getc(void)
{
	while (!_file.eof()) // && _index < _current_line.size())
	{
		if (_index == _current_line.size())
		{
			_index = 0;
			getline(_file, _current_line);
		}
		else if (isblank(_current_line[_index]))
			ignore_blank();
		else
			return _current_line[_index++];
	}
	return 0;
}

//
// Private mumber function
//

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
